Bomem:

  From power up:
    Bring up cygwin window
    Run /usr/sbin/xinetd
  
    Bring up Bomem Acquire

  At start of run:
    Run Macro specd.mac


QNX:
  cd /home/radlab
  ./doit
  Wait for macro initialization (~1 minute)
  
  If initialization fails, go to Bomem computer and:
    alt-tab to get back to cygwin window
    cd /home/radlab
    echo quit >specdcmd.txt
    alt-tab back to Bomem Acquire
    repeat as necessary

  ---The following is not yet implemented---
  If macro initialization succeeds, you will see
    "Waiting for synchronization"
    
    > SW Status Synchronize
    
    will begin the first scan immediately
    
    > SW Status Shutdown
    
    will wait until the current scans are done,
    then terminate the macro and quit. If the
    macro termination fails, see procedure above.
 
  After quitting on QNX:
    reduce

