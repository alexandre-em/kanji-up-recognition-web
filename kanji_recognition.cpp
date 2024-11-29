#include "tensorflow/tensorflow/lite/interpreter.h"
#include "tensorflow/tensorflow/lite/kernels/register.h"
#include "tensorflow/tensorflow/lite/model.h"
#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "kanji_model_data.h"

// Image preprocessing function
std::vector<float> preprocessImage(const std::string& imagePath) {
    cv::Mat img = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    cv::resize(img, img, cv::Size(64, 64));    // Resizing to model's expected input
    img.convertTo(img, CV_32F, 1.0 / 255);     // Normalizing
    return std::vector<float>(img.begin<float>(), img.end<float>());
}

int runModel(const std::string& imagePath) {
    // Load the model from memory
    auto model = tflite::FlatBufferModel::BuildFromBuffer(
        reinterpret_cast<const char*>(assets_kanji_model_tflite), assets_kanji_model_tflite_len);
    if (!model) {
        std::cerr << "Failed to load model from memory.\n";
        return -1;
    }

    // Build the interpreter
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);
    if (!interpreter) {
        std::cerr << "Failed to create interpreter.\n";
        return -1;
    }

    interpreter->AllocateTensors();

    // Preprocess the image
    std::vector<float> input = preprocessImage(imagePath);
    float* inputTensor = interpreter->typed_input_tensor<float>(0);
    std::copy(input.begin(), input.end(), inputTensor);

    // Run inference
    if (interpreter->Invoke() != kTfLiteOk) {
        std::cerr << "Failed to invoke TFLite interpreter.\n";
        return -1;
    }

    // Process output (example assumes single output)
    float* outputTensor = interpreter->typed_output_tensor<float>(0);
    std::cout << "Prediction: " << outputTensor[0] << std::endl;

    return 0;
}
