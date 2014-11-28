#ifndef READ_TEC_H
#define READ_TEC_H
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QMap>
class TEC_DATA
{
    QString Title;
    QString Zone_name;
    int N;
    int E;
  public:
    QList<float> Coord_x;
    QList<float> Coord_y;
    QList<float> Coord_z;
    QMap<QString,QList<float>> values;
    QList<QList<int>> Cell;
private:
    int dim;
    int value_number;
    QList<QString> value_name;

public:

    void setZone_name(QString z)
    {
        this->Zone_name = z;
    }
    QString getZone_name()
    {
        return Zone_name;
    }
    void setValue_name(QList<QString> v)
    {
        this->value_name = v;
    }
    QList<QString> getValue_Name()
    {
        return this->value_name;
    }
    void SetVlaueN(int n)
    {
        this->value_number = n;
    }
    int GetValueN()
    {
        return this->value_number;
    }


    void  SetTitle(QString name)
    {
       this->Title = name;
    }

    QString GetTitle()
    {
        return this->Title;
    }

    void SetDim(int dim)
    {
        this->dim = dim;

    }

    int GetDim( )
    {
        return dim;
    }

    void SetN(int N)
    {
        this->N = N;
    }

    int GetN()
    {
        return this->N;
    }

    void SetE(int E)
    {
        this->E = E;
    }

    int GetE()
    {
        return E;
    }


};




class Read_Tec
{
public:
    Read_Tec();
    TEC_DATA* tec_data;
    void read_tec(QString filename);
private:
   int read_title(QTextStream &in);
   int read_varibles(QTextStream& in);
   int read_points(QTextStream& in);
   int read_cells(QTextStream& in);
   int read_zones(QTextStream& in);
   int dim ;
   int value_n;
   int N;
   int E;
   QList<QString> value_name;
   QString zone_name;

};

#endif // READ_TEC_H
