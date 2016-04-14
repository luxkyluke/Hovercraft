#ifndef Point2D_H_
#define Point2D_H_

typedef struct {
    float x, y;
} Point2D;

Point2D PointXY(float x, float y);
Point2D AddPoints(Point2D u, Point2D v);

#endif
