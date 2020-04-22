`timescale 1ns / 1ps
module test_multi;
    reg clk;
    reg rst;
    reg [7:0] A00;
    reg [7:0] A01;
    reg [7:0] A02;
    reg [7:0] A03;
    reg [7:0] A10;
    reg [7:0] A11;
    reg [7:0] A12;
    reg [7:0] A13;
    reg [7:0] A20;
    reg [7:0] A21;
    reg [7:0] A22;
    reg [7:0] A23;
    reg [7:0] A30;
    reg [7:0] A31;
    reg [7:0] A32;
    reg [7:0] A33;
    reg [7:0] B00;
    reg [7:0] B01;
    reg [7:0] B02;
    reg [7:0] B03;
    reg [7:0] B10;
    reg [7:0] B11;
    reg [7:0] B12;
    reg [7:0] B13;
    reg [7:0] B20;
    reg [7:0] B21;
    reg [7:0] B22;
    reg [7:0] B23;
    reg [7:0] B30;
    reg [7:0] B31;
    reg [7:0] B32;
    reg [7:0] B33;
    wire [7:0] Result00;
    wire [7:0] Result01;
    wire [7:0] Result02;
    wire [7:0] Result03;
    wire [7:0] Result10;
    wire [7:0] Result11;
    wire [7:0] Result12;
    wire [7:0] Result13;
    wire [7:0] Result20;
    wire [7:0] Result21;
    wire [7:0] Result22;
    wire [7:0] Result23;
    wire [7:0] Result30;
    wire [7:0] Result31;
    wire [7:0] Result32;
    wire [7:0] Result33;

    
    matrixMulti matrixMultiTest(.clk(clk),
                                .rst(rst),
                                .A00(A00),
                                .A01(A01),
                                .A02(A02),
                                .A03(A03),
                                .A10(A10),
                                .A11(A11),
                                .A12(A12),
                                .A13(A13),
                                .A20(A20),
                                .A21(A21),
                                .A22(A22),
                                .A23(A23),
                                .A30(A30),
                                .A31(A31),
                                .A32(A32),
                                .A33(A33),
                                .B00(B00),
                                .B01(B01),
                                .B02(B02),
                                .B03(B03),
                                .B10(B10),
                                .B11(B11),
                                .B12(B12),
                                .B13(B13),
                                .B20(B20),
                                .B21(B21),
                                .B22(B22),
                                .B23(B23),
                                .B30(B30),
                                .B31(B31),
                                .B32(B32),
                                .B33(B33),
                                .Result00(Result00),
                                .Result01(Result01),
                                .Result02(Result02),
                                .Result03(Result03),
                                .Result10(Result10),
                                .Result11(Result11),
                                .Result12(Result12),
                                .Result13(Result13),
                                .Result20(Result20),
                                .Result21(Result21),
                                .Result22(Result22),
                                .Result23(Result23),
                                .Result30(Result30),
                                .Result31(Result31),
                                .Result32(Result32),
                                .Result33(Result33)
                                );
    
    initial begin
        clk = 0;
        rst = 1;
        A00 = 5;
        A01 = 6;
        A02 = 7;
        A03 = 8;
        A10 = 10;
        A11 = 12;
        A12 = 14;
        A13 = 16;
        A20 = 15;
        A21 = 18;
        A22 = 21;
        A23 = 24;
        A30 = 20;
        A31 = 24;
        A32 = 28;
        A33 = 32;
        B00 = 115;
        B01 = 138;
        B02 = 161;
        B03 = 184;
        B10 = 120;
        B11 = 144;
        B12 = 168;
        B13 = 192;
        B20 = 125;
        B21 = 150;
        B22 = 175;
        B23 = 200;
        B30 = 130;
        B31 = 156;
        B32 = 182;
        B33 = 208;
        #20 rst = 0;
    end
    initial forever #10 clk = ~clk;
endmodule
