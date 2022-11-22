#include <iostream>
#include <P1Image.hpp>
// basic file operations
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


int main(int argc, const char** argv)
{

   if(argc != 3 ) {
      cout << "2 argument must be provided to run the program.";
      return -1;
   }

   // first argument is the json file
   std::ifstream f(argv[1]);
   cout << "past stream";
   // parse json file
   json object = json::parse(f);
   cout << "past parse";

   // build a json empty array 
   json outputJson;
   outputJson = json::array();

   for (auto& el : object["paths"].items())
   {
      string input = el.value()["input"];
      string outputPendingTiff = el.value()["outputPendingTiff"];

      try{
         // Open an IIQ-file     
         P1::ImageSdk::RawImage iiq(input);

         // Setup a convert config with the description about how to convert image into Rgb domain
         P1::ImageSdk::ConvertConfig config;
         config.SetOutputScale(1);

         P1::ImageSdk::SetSensorProfilesLocation("/data/pipeline/terramap-repo/packages/order-service/scripts/PhaseOne/conversion/build/SensorProfiles");
         P1::ImageSdk::BitmapImage bitmap = iiq.Convert(config);

         // The resulting bitmap can now be stored to a tiff file.   
         P1::ImageSdk::TiffConfig tiff;
         P1::ImageSdk::TiffWriter(outputPendingTiff, bitmap, iiq, tiff);

         std::cout << "iiq to tiff conversion complete!" << std::endl;

         // create an empty structure (null)
         json fileDetails;
         fileDetails["input"] = input;
         fileDetails["outputPendingTiff"] = outputPendingTiff;
         fileDetails["finalOutput"] = el.value()["finalOutput"]; // pass this along for next step
         fileDetails["orderId"] = el.value()["orderId"]; // pass this along for next step
         fileDetails["originalFilename"] = el.value()["originalFilename"]; // pass this along for next step
         fileDetails["success"] = true;
         outputJson.push_back(fileDetails);
         } catch ( ... ) {
         std::cout << "Error converting image from iiq to tiff" << std::endl;
         // create an empty structure (null)
         json fileDetails;
         fileDetails["input"] = input;
         fileDetails["outputPendingTiff"] = outputPendingTiff;
         fileDetails["finalOutput"] = el.value()["finalOutput"]; // pass this along for next step
         fileDetails["orderId"] = el.value()["orderId"]; // pass this along for next step
         fileDetails["originalFilename"] = el.value()["originalFilename"]; // pass this along for next step
         fileDetails["success"] = false;
         outputJson.push_back(fileDetails);
      };
   }

   // write json file
   std::ofstream file(argv[2]);
   file << outputJson;

   return 0;
}
