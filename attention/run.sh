# Using iverilog to generate from .v documents.
iverilog -o wave attention/pe.v attention/test_pe.v

# vvp Icarus Verilog vvp runtime engine.
vvp -n wave

# Use gtkwave to show the wave.
gtkwave wave.vcd