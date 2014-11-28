#include <QCoreApplication>
#include "read_tec.h"
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)
#include <vtk/vtkRenderer.h>
#include <vtk/vtkRenderWindow.h>
#include <vtk/vtkRenderWindowInteractor.h>
#include <vtk/vtkDICOMImageReader.h>
#include <vtk/vtkPolyDataMapper.h>
#include <vtk/vtkActor.h>
#include <vtk/vtkOutlineFilter.h>
#include <vtk/vtkCamera.h>
#include <vtk/vtkProperty.h>
#include <vtk/vtkPolyDataNormals.h>
#include <vtk/vtkContourFilter.h>
#include <vtk/vtkInteractorStyleTrackballCamera.h>
#include <vtk/vtkStructuredGrid.h>
#include <vtk/vtkPoints.h>
#include <vtk/vtkSmartPointer.h>
#include <vtk/vtkStructuredGridOutlineFilter.h>
#include <vtk/vtkDataSetMapper.h>
#include <vtk/vtkStructuredGridGeometryFilter.h>
#include <vtk/vtkUnstructuredGrid.h>
#include <vtk/vtkUnstructuredGridGeometryFilter.h>
#include <vtk/vtkDoubleArray.h>
#include <vtk/vtkArrowSource.h>
#include <vtk/vtkCellArray.h>
#include <vtk/vtkGlyph2D.h>
#include <vtk/vtkPointData.h>
#include <vtk/vtkImageData.h>
#include <vtk/vtkImageSliceMapper.h>
#include <vtk/vtkImageSlice.h>
#include <vtk/vtkInteractorStyleImage.h>
#include <vtk/vtkPolyDataMapper.h>
#include <vtk/vtkPolyData.h>
#include <vtk/vtkPoints.h>
#include <vtk/vtkRenderer.h>
#include <vtk/vtkRenderWindow.h>
#include <vtk/vtkRenderWindowInteractor.h>
#include <vtk/vtkSmartPointer.h>
#include <vtk/vtkXMLPolyDataWriter.h>
#include <vtk/vtkVersion.h>
#include <vtk/vtkUnstructuredGrid.h>
#include <vtk/vtkPolyVertex.h>
#include <vtk/vtkDataSetMapper.h>
#include <vtk/vtkProperty.h>
#include <vtk/vtkDoubleArray.h>
#include <vtk/vtkPolyhedron.h>
#include <vtk/vtkPointLocator.h>
#include <QDebug>
#include <vtk/vtkContourFilter.h>
#include <vtk/vtkGaussianSplatter.h>
#include <vtk/vtkAxes.h>
#include <vtk/vtkTubeFilter.h>
#include <vtk/vtkStripper.h>
#include <vtk/vtkLookupTable.h>
#include <vtk/vtkDelaunay3D.h>
#include <vtk/vtkDelaunay2D.h>
#include <vtk/vtkLabeledDataMapper.h>
#include <vtk/vtkActor2D.h>
#include <vtk/vtkGlyph3D.h>
#include <vtk/vtkCleanPolyData.h>
#include <vtk/vtkPlaneSource.h>
#include <vtk/vtkMath.h>

#include <vtk/vtkBandedPolyDataContourFilter.h>
#include <vtk/vtkNamedColors.h>
#include <vtk/vtkScalarBarActor.h>
#include <vtk/vtkColorTransferFunction.h>
#include <vtk/vtkSmoothPolyDataFilter.h>
#include <vtk/vtkPolyDataNormals.h>
#include <vtk/vtkTextProperty.h>
#include <vtk/vtkStripper.h>
#include <vtk/vtkPolyDataNormals.h>
#include <vtk/vtkMarchingCubes.h>
#include <vtk/vtkDecimatePro.h>
#include <vtk/vtkVoxelModeller.h>
#include <vtk/vtkCleanPolyData.h>
#include <vtk/vtkReverseSense.h>
#include <vtk/vtkHedgeHog.h>

#include <vtk/vtkDataSetTriangleFilter.h>
#include <vtk/vtkWarpScalar.h>
#include <vtk/vtkShepardMethod.h>
#include <vtk/vtkGeometryFilter.h>
#include <vtk/vtkExtractVOI.h>
#include <vtk/vtkBandedPolyDataContourFilter.h>
#include <vtk/vtkSurfaceReconstructionFilter.h>
#include <vtk/vtkProbeFilter.h>
#include <vtk/vtkWindowedSincPolyDataFilter.h>
#include <vtk/vtkStructuredGrid.h>
#include <vtk/vtkIntArray.h>
#include <vtk/vtkCellData.h>


#define VTK_NEW(type, instance); vtkSmartPointer<type> instance = vtkSmartPointer<type>::New();
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename = "C:\\Users\\jjwang\\Documents\\Tencent Files\\1020181331\\FileRecv\\1.dat";
    Read_Tec read_tec;
    read_tec.read_tec(filename);
    //return a.exec();
    // Create the renderer, the render window, and the interactor. The renderer
          // draws into the render window, the interactor enables mouse- and
          // keyboard-based interaction with the data within the render window.
          vtkRenderer *Render = vtkRenderer::New();
          vtkRenderWindow *renWin = vtkRenderWindow::New();
            renWin->AddRenderer(Render);
          vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();
          vtkRenderWindowInteractor *ireninter = vtkRenderWindowInteractor::New();
            ireninter->SetInteractorStyle(style);
            ireninter->SetRenderWindow(renWin);

 int Nx,Ny,Nz;

int N = read_tec.tec_data->GetN();
int dim = read_tec.tec_data->GetDim();
 vtkSmartPointer<vtkPoints> points =
     vtkSmartPointer<vtkPoints>::New();
 points->SetNumberOfPoints(N);
 for(int i=0;i<N ;i++)
 {

             float x,y,z;
             if( dim == 3)
             {
                 x = read_tec.tec_data->Coord_x.at(i);
                 y = read_tec.tec_data->Coord_y.at(i);
                 z = read_tec.tec_data->Coord_z.at(i);
                 //points->InsertNextPoint(x,y,z);
                 points->InsertPoint(i,x,y,z);
             }

 }
 vtkSmartPointer<vtkUnstructuredGrid> structuredGrid =
     vtkSmartPointer<vtkUnstructuredGrid>::New();

int scaler_size = read_tec.tec_data->getValue_Name().size();
QList<QString> scaler_names = read_tec.tec_data->getValue_Name();
QList<float>  select_points = read_tec.tec_data->values.value(scaler_names.at(0));
qDebug()<<select_points.size()<<N;
//set scalar
vtkSmartPointer<vtkDoubleArray> pointDataArray =
           vtkSmartPointer<vtkDoubleArray>::New();

vtkSmartPointer<vtkDoubleArray> scalars =
           vtkSmartPointer<vtkDoubleArray>::New();
pointDataArray->Initialize();
pointDataArray->SetNumberOfComponents(3);
for(int i=0;i<N;i++)
{
    scalars->InsertValue(i,select_points.at(i));
    pointDataArray->InsertNextTuple3(select_points.at(i),0,0);
}

vtkSmartPointer<vtkIntArray> cell_code =
           vtkSmartPointer<vtkIntArray>::New();
 int E = read_tec.tec_data->GetE();
 cell_code->SetName("cell_code");
 cell_code->SetNumberOfValues(E);
 structuredGrid->GetCellData()->AddArray(cell_code);
 for (vtkIdType i = 0; i < E; ++i) {

   vtkIdType pts[8];


  QList<int> temp = read_tec.tec_data->Cell.at(i);


   if (temp.size() == 3) { // triangle
     for (vtkIdType j = 0; j < 3; ++j) {
       pts[j] = temp.at(j);
     }
     structuredGrid->InsertNextCell(VTK_TRIANGLE,3,pts);
   } else if (temp.size() == 4) { // quad
     for (vtkIdType j = 0; j < 4; ++j) {

       pts[j] =  temp.at(j);
     }
     structuredGrid->InsertNextCell(VTK_QUAD,4,pts);

   }
 }



 structuredGrid->SetPoints(points);
 structuredGrid->GetPointData()->SetVectors(pointDataArray);
structuredGrid->GetPointData()->SetScalars(scalars);

   double range[2];

   structuredGrid->GetScalarRange(range);
 VTK_NEW(vtkLookupTable,lookUpTable);
    lookUpTable->SetRampToLinear();
    lookUpTable->SetNumberOfColors( 256 );
    lookUpTable->SetHueRange(0.667,0.0);
    lookUpTable->SetRange(range);
    lookUpTable->Build();


    vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();

       arrowSource->Update();
 vtkSmartPointer<vtkGlyph3D> glyphFilter = vtkSmartPointer<vtkGlyph3D>::New();
      glyphFilter->SetSourceConnection(arrowSource->GetOutputPort());
      glyphFilter->OrientOn();
      glyphFilter->SetVectorModeToUseVector();


      glyphFilter->SetScaleFactor(0.001);
      glyphFilter->SetInputData(structuredGrid);
      glyphFilter->SetVectorModeToUseNormal();
      glyphFilter->SetVectorModeToUseVector();
      glyphFilter->SetScaleModeToDataScalingOff();
      glyphFilter->GeneratePointIdsOn();
      glyphFilter->SetColorModeToColorByVector();
      glyphFilter->Update();
      vtkSmartPointer<vtkPolyDataMapper> vectorMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      vectorMapper->SetInputConnection(glyphFilter->GetOutputPort());
      vectorMapper->SetLookupTable(lookUpTable);
      vectorMapper->SetScalarRange(range);

      vectorMapper->SetScalarModeToUsePointData();
       vectorMapper->SetColorModeToMapScalars();
      vectorMapper->SetScalarVisibility(1);
      vectorMapper->UseLookupTableScalarRangeOn();





 std::cout << "There are " << structuredGrid->GetNumberOfPoints() << " points." << std::endl; // there should be 2*3*2 = 12 points
   std::cout << "There are " << structuredGrid->GetNumberOfCells() << " cells." << std::endl; // The 12 points define the corners of 2 cubes/cells (4 points are shared by both cubes)



   vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(vectorMapper);
     actor->GetProperty()->SetPointSize(3);





     VTK_NEW(vtkShepardMethod,shep);
     shep->SetInputData(structuredGrid);
     shep->SetNullValue(range[0]);
     shep->SetMaximumDistance(1);
     shep->SetModelBounds(structuredGrid->GetBounds());
     shep->SetSampleDimensions(20,20,20);
     shep->Update();



//     vtkSmartPointer<vtkDelaunay3D> delaunay
//               = vtkSmartPointer<vtkDelaunay3D>::New();

//            delaunay->SetTolerance(0.01);
//            delaunay->SetInputData(structuredGrid);
//  //delaunay->SetInputConnection(cleanPolyData->GetOutputPort());
//           // delaunay->SetAlpha(100);
//            delaunay->Update();


                      vtkGaussianSplatter *popSplatter = vtkGaussianSplatter::New();
                         popSplatter->SetInputData(structuredGrid);
                         popSplatter->SetSampleDimensions(10,10,10);
                         popSplatter->SetRadius(0.1);
                         popSplatter->SetScaleFactor(0.1);
                         popSplatter->SetModelBounds(structuredGrid->GetBounds());
                         popSplatter->ScalarWarpingOff();
                         popSplatter->NormalWarpingOn();
                         popSplatter->SetExponentFactor(-1);
                         popSplatter->Update();


     vtkSmartPointer<vtkContourFilter> popSurface2 =
     vtkSmartPointer<vtkContourFilter>::New();
     popSurface2->SetInputConnection(popSplatter->GetOutputPort());
      // popSurface2->SetInputData(structuredGrid);
     popSurface2->GenerateValues(20, range[0], range[1]);
     popSurface2->Update();

     vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
         skinNormals->SetInputConnection(popSurface2->GetOutputPort());
         skinNormals->SetFeatureAngle(60.0);
         vtkStripper *skinStripper = vtkStripper::New();
         skinStripper->SetInputConnection(skinNormals->GetOutputPort());

     vtkSmartPointer<vtkPolyDataMapper> vectorMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
     vectorMapper2->SetInputConnection(skinStripper->GetOutputPort());

     vectorMapper2->SetScalarRange(range);
      vectorMapper2->SetLookupTable(lookUpTable);

     vectorMapper2->SetScalarVisibility(1);
     vectorMapper2->UseLookupTableScalarRangeOn();
     vectorMapper2->SetColorModeToMapScalars();
     vectorMapper2->Update();
     vtkSmartPointer<vtkActor> vectorActor2 = vtkSmartPointer<vtkActor>::New();
     vectorActor2->SetMapper(vectorMapper2);











   // Visualize
   vtkSmartPointer<vtkRenderer> renderer =
       vtkSmartPointer<vtkRenderer>::New();
   vtkSmartPointer<vtkRenderWindow> renderWindow =
       vtkSmartPointer<vtkRenderWindow>::New();
   renderWindow->AddRenderer(renderer);
   vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
       vtkSmartPointer<vtkRenderWindowInteractor>::New();
   renderWindowInteractor->SetRenderWindow(renderWindow);
  // renderer->SetBackground(.3, .6, .3); // Background color green
    renderer->AddActor(actor);
   //renderer->SetBackground(1,1,1); // Background color white
  renderer->AddActor(vectorActor2);
   renderWindow->Render();
   renderWindowInteractor->Start();




          return 0;
}
