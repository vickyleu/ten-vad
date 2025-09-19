//
// Copyright © 2025 Agora
// This file is part of TEN Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ten_vad.h"

int main(int argc, char* argv[]) {
    printf("TEN-VAD Custom Model Path Example\n");
    printf("==================================\n\n");

    // 检查命令行参数
    const char* model_path = NULL;
    if (argc > 1) {
        model_path = argv[1];
        printf("Using custom model path: %s\n", model_path);
    } else {
        printf("No custom model path provided, will use:\n");
        printf("1. Environment variable TEN_VAD_MODEL_PATH (if set)\n");
        printf("2. Default path: onnx_model/ten-vad.onnx\n\n");
    }

    // 创建VAD实例
    ten_vad_handle_t vad_handle = NULL;
    int result;
    
    if (model_path != NULL) {
        // 使用自定义模型路径
        result = ten_vad_create_with_model(&vad_handle, 256, 0.5f, model_path);
    } else {
        // 使用默认配置（环境变量或默认路径）
        result = ten_vad_create(&vad_handle, 256, 0.5f);
    }

    if (result != 0) {
        printf("Failed to create VAD instance\n");
        return -1;
    }

    printf("VAD instance created successfully!\n");

    // 模拟音频数据处理
    int16_t audio_data[256];
    float probability;
    int vad_flag;

    // 生成一些测试音频数据（静音）
    memset(audio_data, 0, sizeof(audio_data));

    // 处理音频帧
    result = ten_vad_process(vad_handle, audio_data, 256, &probability, &vad_flag);
    if (result == 0) {
        printf("VAD processing successful:\n");
        printf("  Voice probability: %.3f\n", probability);
        printf("  VAD flag: %d\n", vad_flag);
    } else {
        printf("VAD processing failed\n");
    }

    // 清理资源
    ten_vad_destroy(&vad_handle);
    printf("\nVAD instance destroyed\n");

    return 0;
}
