#pragma once
#include <vector>
#include <mutex>
#include <core/framework/ml_value.h>
#include <experimental/filesystem>
#ifdef _MSC_VER
#include <filesystem>
#endif

namespace onnx {
class ValueInfoProto;
}

//One test case is for one model file
//One test case can contain multiple test data(input/output pairs)
class ITestCase {
 public:
  //must be called before calling the other functions
  virtual ::onnxruntime::common::Status SetModelPath(const std::experimental::filesystem::v1::path& path) = 0;
  virtual ::onnxruntime::common::Status LoadInputData(size_t id, std::unordered_map<std::string, ::onnxruntime::MLValue>& feeds) = 0;
  virtual ::onnxruntime::common::Status LoadOutputData(size_t id, std::vector<::onnxruntime::MLValue>& output_values) = 0;
  virtual const std::experimental::filesystem::v1::path& GetModelUrl() const = 0;
  virtual const std::string& GetTestCaseName() const = 0;
  virtual void SetAllocator(const ::onnxruntime::AllocatorPtr&) = 0;
  //a string to help identify the dataset
  virtual std::string GetDatasetDebugInfoString(size_t dataset_id) = 0;
  virtual ::onnxruntime::common::Status GetNodeName(std::string* out) = 0;
  //The number of input/output pairs
  virtual size_t GetDataCount() const = 0;
  virtual const onnx::ValueInfoProto& GetOutputInfoFromModel(size_t i) const = 0;
  virtual ~ITestCase() {}
  virtual ::onnxruntime::common::Status GetPerSampleTolerance(double* value) = 0;
  virtual ::onnxruntime::common::Status GetRelativePerSampleTolerance(double* value) = 0;
  virtual ::onnxruntime::common::Status GetPostProcessing(bool* value) = 0;
};

ITestCase* CreateOnnxTestCase(const ::onnxruntime::AllocatorPtr&, const std::string& test_case_name);
ITestCase* CreateOnnxTestCase(const std::string& test_case_name);
