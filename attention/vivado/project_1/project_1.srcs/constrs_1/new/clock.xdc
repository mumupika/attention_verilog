create_clock -period 10.000 -name clk1 -waveform {0.000 5.000} -add [get_ports clk]

set_property PACKAGE_PIN A10 [get_ports clk]
set_property PACKAGE_PIN A8 [get_ports en]
set_property PACKAGE_PIN A9 [get_ports rst_n]
set_property PACKAGE_PIN C13 [get_ports all_done]

set_input_delay -clock [get_clocks *] -add_delay 1.500 [get_ports -filter { NAME =~  "*" && DIRECTION == "IN" }]
set_output_delay -clock [get_clocks *] -add_delay 1.500 [get_ports -filter { NAME =~  "*" && DIRECTION == "OUT" }]



