/**
 * @class   vtkF3DQuakeMDLImporter
 * @brief   VTK Importer for Quake 1 models in .mdl file format
 *
 * This reader is based on implementations of Quake 1's MDL, defined in
 * https://book.leveldesignbook.com/appendix/resources/formats/mdl It reads vertices, normals and
 * texture coordinate data from .mdl files. Supports animations.
 */

#ifndef vtkF3DQuakeMDLImporter_h
#define vtkF3DQuakeMDLImporter_h

#include <vtkF3DImporter.h>

class vtkF3DQuakeMDLImporter : public vtkF3DImporter
{
public:
  static vtkF3DQuakeMDLImporter* New();

  /**
   * Set the file name.
   */
  vtkSetMacro(FileName, std::string);

  /**
   * Update actors at the given time value.
   */
  bool UpdateAtTimeValue(double timeValue) override;

  /**
   * Get the number of available animations.
   */
  vtkIdType GetNumberOfAnimations() override;

  /**
   * Return the name of the animation.
   */
  std::string GetAnimationName(vtkIdType animationIndex) override;

  ///@{
  /**
   * Enable/Disable/Get the status of specific animations
   */
  void EnableAnimation(vtkIdType animationIndex) override;
  void DisableAnimation(vtkIdType animationIndex) override;
  bool IsAnimationEnabled(vtkIdType animationIndex) override;
  ///@}

  /**
   * Get temporal information for the currently enabled animations.
   */
  bool GetTemporalInformation(vtkIdType animationIndex, double frameRate, int& nbTimeSteps,
    double timeRange[2], vtkDoubleArray* timeSteps) override;

protected:
  vtkF3DQuakeMDLImporter();
  ~vtkF3DQuakeMDLImporter() override = default;

  int ImportBegin() override;
  void ImportActors(vtkRenderer*) override;

private:
  vtkF3DQuakeMDLImporter(const vtkF3DQuakeMDLImporter&) = delete;
  void operator=(const vtkF3DQuakeMDLImporter&) = delete;

  class vtkInternals;
  std::string FileName;

  std::unique_ptr<vtkInternals> Internals;
};

#endif
