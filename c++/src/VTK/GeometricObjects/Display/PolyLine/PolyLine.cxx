#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLPolyDataWriter.h>

int main(int argc, char *argv[])
{
  // Create three points. We will join (Origin and P0) with a red line and (Origin and P1) with a green line
  double origin[3] = {0.0, 0.0, 0.0};
  double p0[3] = {1.0, 0.0, 0.0};
  double p1[3] = {0.0, 1.0, 0.0};
  double p2[3] = {0.0, 1.0, 2.0};
  double p3[3] = {1.0, 2.0, 3.0};
    
  // Create a vtkPoints object and store the points in it
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(origin);
  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);

  vtkSmartPointer<vtkPolyLine> polyLine = 
      vtkSmartPointer<vtkPolyLine>::New();
  polyLine->GetPointIds()->SetNumberOfIds(5);
  for(unsigned int i = 0; i < 5; i++)
    {
    polyLine->GetPointIds()->SetId(i,i);
    }

  //Create a cell array to store the lines in and add the lines to it
  vtkSmartPointer<vtkCellArray> cells = 
      vtkSmartPointer<vtkCellArray>::New();
  cells->InsertNextCell(polyLine);
  
  //Create a polydata to store everything in
  vtkSmartPointer<vtkPolyData> polyData = 
      vtkSmartPointer<vtkPolyData>::New();
  
  //add the points to the dataset
  polyData->SetPoints(points);
  
  //add the lines to the dataset
  polyData->SetLines(cells);
  
  vtkSmartPointer<vtkXMLPolyDataWriter> writer =
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("/home/doriad/line.vtp");
  writer->SetInput(polyData);
  writer->Write();
  
  //setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInput(polyData);
  
  vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  //setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);

  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}