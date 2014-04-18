#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "../CommandBase.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"



class Autonomous: public CommandBase
{

private:

/*	
	void VisionLoop();
	double computeDistance (BinaryImage *image, ParticleAnalysisReport *report, bool outer);
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool outer);
//	bool scoreCompare(Scores scores, bool outer);
	double scoreRectangularity(ParticleAnalysisReport *report);
	double scoreXEdge(BinaryImage *image, ParticleAnalysisReport *report);
	double scoreYEdge(BinaryImage *image, ParticleAnalysisReport *report);
	*/
public:
	Autonomous();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
