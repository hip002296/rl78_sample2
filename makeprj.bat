set path=C:\Program Files (x86)\Renesas Electronics\CS+\CC\CC-RL\V1.13.00\bin;%PATH%
C:
CD "C:\Users\h_umemura\My Documents\Applilet EZ PL for RL78\Project\RL78_Sample2"
DEL obj\*.obj
DEL obj\*.asm
"asrl.exe" @cstart.pst >> "RL78_Sample2.err" 2>&1
"asrl.exe" @opt_byte.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=main.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @main.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=common.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @common.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=timer.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @timer.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=int.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @int.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=port.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @port.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=watchdogtimer.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @watchdogtimer.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=system.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @system.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=systeminit.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @systeminit.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=panel.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @panel.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=digitalio.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @digitalio.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=counter.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @counter.pst >> "RL78_Sample2.err" 2>&1
"ccrl.exe" -subcommand=74hc.pcc >> "RL78_Sample2.err" 2>&1
"asrl.exe" @74hc.pst >> "RL78_Sample2.err" 2>&1

"rlink.exe" -SUbcommand="RL78_Sample2.plk" >> "RL78_Sample2.err" 2>&1
