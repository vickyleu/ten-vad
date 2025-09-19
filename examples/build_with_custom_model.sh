#!/bin/bash

# Copyright © 2025 Agora
# This file is part of TEN Framework, an open source project.
# Licensed under the Apache License, Version 2.0, with certain conditions.
# Refer to the "LICENSE" file in the root directory for more information.

set -e

echo "Building TEN-VAD with custom model path support..."

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"

# 设置ONNX Runtime路径（需要根据实际安装路径调整）
if [ -z "$ORT_ROOT" ]; then
    echo "Warning: ORT_ROOT environment variable not set. Please set it to your ONNX Runtime installation path."
    echo "Example: export ORT_ROOT=/path/to/onnxruntime"
    exit 1
fi

# 创建构建目录
BUILD_DIR="$ROOT_DIR/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 配置CMake
echo "Configuring CMake..."
cmake -DORT_ROOT="$ORT_ROOT" "$ROOT_DIR/examples_onnx"

# 编译
echo "Building..."
make -j$(nproc)

echo "Build completed successfully!"
echo ""
echo "Usage examples:"
echo "1. Using default model path:"
echo "   ./ten_vad_demo"
echo ""
echo "2. Using custom model path:"
echo "   ./ten_vad_demo /path/to/your/model.onnx"
echo ""
echo "3. Using environment variable:"
echo "   export TEN_VAD_MODEL_PATH=/path/to/your/model.onnx"
echo "   ./ten_vad_demo"
echo ""
echo "4. Using absolute path (recommended for production):"
echo "   ./ten_vad_demo /var/lib/wukong/onnx_model/ten-vad.onnx"
