#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

typedef	struct {
	Point2D position;
	float radius;
}Checkpoint;

void MakeCheckpoint(Point2D pos, float r);
bool EstSurCheckpoint(Point2D pos);

#endif