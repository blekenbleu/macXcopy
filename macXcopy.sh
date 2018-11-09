if [ -z "`ps a | grep maccopy | grep -v grep`" ] ; then
   /usr/local/bin/maccopy > /dev/null 2>&1 &
fi
