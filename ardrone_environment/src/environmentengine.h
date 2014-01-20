#ifndef ENVIRONMENTENGINE_H
#define ENVIRONMENTENGINE_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include "opencv/cv.h"
#include "ros_wrapper.h"

#define EMPTY_VALUE 0
#define WALL_VALUE 1


class Environment2D;
class MainWindow;

class EnvironmentEngine : public QObject
{
    Q_OBJECT

public:
    EnvironmentEngine(QObject *parent = 0);
    virtual ~EnvironmentEngine();

    void start();

    bool ready() const;


    void load();
    // Loads params from a xml configuration file
    void loadConfiguration(const QString& configFilename);
    void saveConfiguration(const QString& configFilename);
    void loadConfiguration(const QString &backgroundFilename, const QString &wallMaskFilename, const QString &tagMaskFilename);

    struct Tag
    {
        int id;
        QString code;
        QString value;
        double x;
        double y;
    };

    enum Tile
    {
        EMPTY = EMPTY_VALUE,
        WALL = WALL_VALUE
    };

    // Like QPoint with doubles
    class DoublePoint
    {
    public:
        DoublePoint()
        {
            m_x = 0.0;
            m_y = 0.0;
        }

        DoublePoint(double x, double y)
        {
            m_x = x;
            m_y = y;
        }

        double x() const { return m_x; }
        double y() const { return m_y; }

        void setX(double x) { m_x = x; }
        void setY(double y) { m_y = y; }

        void set(double x, double y) { m_x = x; m_y = y; }

        double m_x, m_y;
    };
    typedef QList<DoublePoint> Path;


    Tile getTile(int x, int y) const;
    QList<Tag> getTagsList() const { return m_tagList; }
    void appendTag(const Tag& t);

    const QSize& getSize() const;
    const DoublePoint& getDronePosition() const;
    const DoublePoint& getDroneImagePosition() const;
    const DoublePoint& getOffset() const;
    double getScale() const;
    void setMission(const Path& p);

    void computeImage();

    void updateDronePosition(int x, int y);

    static IplImage* qImage2IplImage(const QImage& qImage);
    IplImage *getCvImage();
    const QImage& getImage() { return m_currentEnvironmentImage; }

    const EnvironmentEngine::DoublePoint getImagePoint(const EnvironmentEngine::DoublePoint& p);

signals:
    void environmentImagePublished(QImage);
    void dronePositionUpdated();
    void tagListUpdated();

public slots:
    void addTag();
    void removeTag(int pos);

    void setOffset(double x, double y);
    void setOffsetX(double x);
    void setOffsetY(double y);

    void setScale(double s);

    void updateTag(int,QString,QString,double,double);

    void computeTrajectory(QPoint p1, QPoint p2);

private:
    void freeMemory();

    // Ros Wrapper
    ros_wrapper m_rosWrapper;

    /** Represents the environment image that will be published by ROS
     *
     */
    QImage m_currentEnvironmentImage;

    // Background image of the real environment
    QString m_backgroundImageFilename;
    QImage m_backgroundImage;

    // Wall mask filename
    QString m_maskImageFilename;


    // Map size, should be the size of all the images...
    QSize m_size;
    QSize m_imageSize;

    // List of all the tag positions, be careful the coordinates are the ones of the image, not the real ones
    QList<Tag> m_tagList;
    DoublePoint m_dronePosition;
    DoublePoint m_droneImagePosition;

    // Represents the path the drone must fly to reach the target (informational)
    Path m_missionPath;


    // 2D array that represents the map
    Tile **p_tilesArray;

    double m_scale;
    DoublePoint m_offset;

    int m_lastTagId;
    bool m_ready;
};

#endif // ENVIRONMENTENGINE_H
