`timescale 1ns / 1ps
module test_cell;
    reg clk;
    reg rst;
    reg [7:0] a_in;
    reg [7:0] b_in;
    wire [7:0] a_out;
    wire [7:0] b_out;
    wire [7:0] result;
    
    Cell Cell_test(.clk(clk),
                   .rst(rst),
                   .a_in(a_in),
                   .b_in(b_in),
                   .a_out(a_out),
                   .b_out(b_out),
                   .result(result)
                   );
    
    initial begin
        clk = 0;
        rst = 1;
        a_in = 2;
        b_in = 3;
        #20 rst = 0;
    end
    initial forever #10 clk = ~clk;
endmodule
