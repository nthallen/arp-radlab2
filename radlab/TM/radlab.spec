tmcbase = base.tmc idx.tmc hart.tmc /usr/local/share/huarp/flttime.tmc
tmcbase = specq.tmc swstat.tmc
cmdbase = /usr/local/share/huarp/root.cmd /usr/local/share/huarp/idx64.cmd
cmdbase = idxdrv.cmd cmdenbl.cmd specq.cmd dccc.cmd swstat.cmd
cmdbase = daspt.cmd

TGTDIR = $(TGTNODE)/home/radlab
IDISTRIB = Experiment.config doit VERSION
SCRIPT = interact idx.idx64 dccc.dccc

radlabcol : idxcol.tmc -lsubbus
radlabdisp : dstat.tmc idxflag.tmc radlab.tbl
radlabsrvr : -lsubbus
radlabalgo : radlab.tma
radlabext : dstat.tmc radlabext.tmc radlabext.oui
testext : testext.tmc testext.oui
doit : radlab.doit

