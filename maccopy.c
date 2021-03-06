// Public Domain License 2016
//
// Simulate right-handed unix/linux X11 left-mouse-button copy
//
// References:
// https://github.com/lodestone/macpaste
// http://stackoverflow.com/questions/3134901/mouse-tracking-daemon
// http://stackoverflow.com/questions/2379867/simulating-key-press-events-in-mac-os-x#2380280
//
// Compile with:
// gcc -framework ApplicationServices -o maccopy maccopy.c
//
// Start with:
// ./maccopy
//
// Terminate with Ctrl+C

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h> 	// kVK_ANSI_*
#include <sys/time.h> 		// gettimeofday

bool isDragging = 0;
long long prevClickTime = 0;
long long curClickTime = 0;

CGEventTapLocation tapA = kCGAnnotatedSessionEventTap;

#define DOUBLE_CLICK_MILLIS 2500

long long now()
{
    static struct timeval te; 
    gettimeofday( & te, NULL );
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    return milliseconds;
}

static void copy()
{
    CGEventSourceRef source = CGEventSourceCreate( kCGEventSourceStateCombinedSessionState );  
    CGEventRef kbdEventDown = CGEventCreateKeyboardEvent( source, kVK_ANSI_C, 1 );                 
    CGEventRef kbdEventUp   = CGEventCreateKeyboardEvent( source, kVK_ANSI_C, 0 );                 
    CGEventSetFlags( kbdEventDown, kCGEventFlagMaskCommand );
    CGEventPost( tapA, kbdEventDown );
    CGEventPost( tapA, kbdEventUp );
    CFRelease( kbdEventDown );
    CFRelease( kbdEventUp );
    CFRelease( source );
}

static void recordClickTime()
{
    prevClickTime = curClickTime;
    curClickTime = now();
}

static bool isDoubleClick()
{
    int time = ( curClickTime - prevClickTime );

#ifdef DEBUG
    fprintf(stderr, "maccopy ClickTime %d", time);
#endif
    return ( (150 > time) ? 0	// debounce
 	   : (time < DOUBLE_CLICK_MILLIS) );
}

static CGEventRef mouseCallback (
				CGEventTapProxy proxy,
				CGEventType type,
				CGEventRef event,
				void * refcon )
{
    switch ( type )
    {
    	case kCGEventLeftMouseDown:
        	recordClickTime();
    		break;

    	case kCGEventLeftMouseUp:
    		if ( isDoubleClick() || isDragging ) {
    		    copy();
    		}
    		isDragging = 0;
    		break;

    	case kCGEventLeftMouseDragged:
    		isDragging = 1;
    		break;

    	default:
    		break;
    }

    // Pass on the event, we must not modify it anyway, we are a listener
    return event;
}

int main ( int argc, char ** argv )
{
    CGEventMask emask;
    CFMachPortRef myEventTap;
    CFRunLoopSourceRef eventTapRLSrc;

    printf("Quit from command-line foreground with Ctrl+C\n");

    // We want "other" mouse button click-release, such as middle or exotic.
    emask = CGEventMaskBit( kCGEventOtherMouseDown ) |
	    CGEventMaskBit( kCGEventLeftMouseDown )  |
	    CGEventMaskBit( kCGEventLeftMouseUp )    |
	    CGEventMaskBit( kCGEventLeftMouseDragged );

    // Create the Tap
    myEventTap = CGEventTapCreate (
        kCGSessionEventTap,          // Catch all events for current user session
        kCGTailAppendEventTap,       // Append to end of EventTap list
        kCGEventTapOptionListenOnly, // We only listen, we don't modify
        emask,
        & mouseCallback,
        NULL                         // We need no extra data in the callback
    );

    // Create a RunLoop Source for it
    eventTapRLSrc = CFMachPortCreateRunLoopSource(
        kCFAllocatorDefault,
        myEventTap,
        0
    );

    // Add the source to the current RunLoop
    CFRunLoopAddSource(
        CFRunLoopGetCurrent(),
        eventTapRLSrc,
        kCFRunLoopDefaultMode
    );
    
    // Keep the RunLoop running forever
    CFRunLoopRun();

    // Not reached (RunLoop above never stops running)
    return 0;
}
