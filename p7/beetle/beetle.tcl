# beetle.tcl


# Called whenever we replot the points
proc replot val {
        puts stdout "p .c  [.sf.sscroll get]"
        flush stdout
}


set thesound "Silent"

# Create canvas widget
canvas .c -width 600 -height 600 -bg gray70
pack .c -side top

.c create rectangle 100 100 500 500 -fill white -width 3

# Beetle number text button for toggle lifespan
.c create text 100 555 -text "Beetle Number: N/A" -tags ct
.c bind ct <Button-1> { puts stdout "a display"}

# Text  for lifespan
.c create text 100 570 -text "Average Lifetime: N/A" -tags life

# Frame to hold the scrollbar
frame .sf
pack  .sf -expand 1 -fill x

# Scrollbar for scaling view.
scale .sf.sscroll -label "Time Scaling" -length 275 \
  -from 1 -to 50 -orient horiz \
  -showvalue 0
  .sf.sscroll set 10

# Pack them into the frame
pack .sf.sscroll -side right

# Frame for holding buttons
frame .bf
pack  .bf -expand 1 -fill x

# Exit Button
button .bf.exit -text "Exit" -command {exit} -bg gray
pack .bf.exit -side left 

# Sound Button
button .bf.sound -text $thesound -command { puts stdout "b toggle"} -bg DeepSkyBlue
pack .bf.sound -side left

# Time Scale Button
button .bf.bscale -text "Time Scale" -command {puts stdout "c [.sf.sscroll get]"} -bg DeepSkyBlue3
pack .bf.bscale -side lefts