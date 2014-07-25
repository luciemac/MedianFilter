#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMedianImageFilter.h"
#include "MedianFilterCLP.h"
#include <sstream>


int main(int argc, char *argv[])
{
  PARSE_ARGS;

  // Test number of arguments has to be 4
  if(argc < 4)
  {
    std::cerr << "Incorrect command" << std::endl <<" Need : "<< std::endl ;
    std::cerr <<argv[0]<< " inputImage outputImage -r radius" << std::endl ;

    return EXIT_FAILURE ;
  }

  // Test value of radius has to be positive and maximum 6
  if(radius_input < 0 || radius_input > 6)
  {
    std::cerr << "Incorrect value of radius" << std::endl ;
    std::cerr << "Radius has to be positive and maximum 6" << std::endl ;

    return EXIT_FAILURE ;
  }

  //Image Type
  typedef itk::Image<unsigned char, 3> ImageType;

  //Input Image
  typedef itk:: ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(input);


  //Median Filtering
  typedef itk::MedianImageFilter<ImageType,ImageType> FilterType;
  FilterType::Pointer MedianFilter = FilterType::New();
  FilterType::InputSizeType radius;
  radius.Fill(radius_input);
  MedianFilter->SetRadius(radius);
  MedianFilter->SetInput(reader->GetOutput()); //on recupere dans filter toutes les valeurs de l'inputImage


  //Output Image
  typedef itk::ImageFileWriter<ImageType> WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput(MedianFilter->GetOutput());
  writer->SetFileName(output);

  try
    {
      writer->Update();
    }
    catch(itk::ExceptionObject &err)
    {
      std::cerr << err.what() << std::endl ;
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS ;
}







