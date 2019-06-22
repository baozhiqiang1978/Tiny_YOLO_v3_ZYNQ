<project xmlns="com.autoesl.autopilot.project" name="yolo_conv_fp_2019" top="yolo_conv_top">
    <files>
        <file name="../tb/layer_input.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false" csimflags=" -Wno-unknown-pragmas"/>
        <file name="../tb/layer_output_sdk.dat" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false" csimflags=" -Wno-unknown-pragmas"/>
        <file name="../tb/yolo_conv_tb.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas" blackbox="false" csimflags=" -Wno-unknown-pragmas"/>
        <file name="yolo_conv_fp_2019/src/layer_parameter.h" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
        <file name="yolo_conv_fp_2019/src/weight_file.h" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
        <file name="yolo_conv_fp_2019/src/yolo_conv.cpp" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
        <file name="yolo_conv_fp_2019/src/yolo_conv.h" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
        <file name="yolo_conv_fp_2019/src/yolo_fp.h" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
        <file name="yolo_conv_fp_2019/src/yolo_stream.h" sc="0" tb="false" cflags="" blackbox="false" csimflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation argv="">
        <SimFlow name="csim" ldflags="" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>
