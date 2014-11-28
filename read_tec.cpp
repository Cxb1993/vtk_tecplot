#include "read_tec.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <algorithm>
Read_Tec::Read_Tec()
{
    tec_data = new TEC_DATA();
      dim = 0;
      value_n = 0;
      value_name.clear();
}


void Read_Tec::read_tec(QString filename)
{
   QFile file(filename);
   if(!file.open(QIODevice::ReadOnly)) {
       QMessageBox::information(0, "error", file.errorString());
   }
   QTextStream in(&file);
   if(read_title(in))
   {
     //get val
       if(read_varibles(in)){
          this->tec_data->SetDim(dim);
          this->tec_data->setValue_name(value_name);
          this->tec_data->SetVlaueN(value_n);
          // qDebug()<<dim<<value_n<<value_name.at(0);
           //get zone info
           if(read_zones(in)){
               this->tec_data->SetN(N);
               this->tec_data->SetE(E);
               this->tec_data->setZone_name(zone_name);
              // qDebug()<<N<<E<<zone_name;
               read_points(in);
              if( read_cells(in))
              {
//                for(int i=0;i<this->tec_data->Cell.size();i++)
//                {
//                    QList<int> temp = tec_data->Cell.at(i);
//                    for(int j = 0;j< temp.size();j++)
//                    {
//                        qDebug()<<temp.at(j);
//                    }
//                }
              }
//               for(int i=0;i<N;i++)
//                {
//                    qDebug()<<this->tec_data->Coord_x.at(i) <<this->tec_data->Coord_y.at(i)<<this->tec_data->Coord_z.at(i);
//                  for(int j = 0;j < value_n ;j++)
//                    {
//                       QString tkey = value_name.at(j);
//                       qDebug()<<this->tec_data->values.value(tkey).at(i)<<"\r\n";
//                    }
//                }


           }
       }
   }else{
       // QMessageBox::information(0, "error", "title error");
       qDebug()<<"error title";
   }
}

int Read_Tec::read_title(QTextStream& in)
{
    QString line = in.readLine();
    qDebug()<<line;
    if(line.trimmed()!= NULL){
        //split the title
        QString title = line.section("=",0,0);
        QString titlename = line.section("=",1,1);
        if(title.trimmed().toLower() == "title")
        {
            qDebug()<<title<<titlename;
            tec_data->SetTitle(titlename);
            return 1;
        }else{
            return 0;
        }

    }else{
        return 0;
    }

}

int Read_Tec::read_varibles(QTextStream &in)
{
    QString line = in.readLine();
    if(line.trimmed()!= NULL){
        //split the title
        QString variables = line.section("=",0,0);
        QString values = line.section("=",1,1);
        if(variables == NULL || variables.size() == 0)
        {
            return 0;
        }else{
             QRegExp rx("\"*\" *,");
             int pos = values.indexOf(rx);              // 0, position of the first match.
                                                      // Returns -1 if str is not found.

             // You can also use rx.indexIn(str);

             qDebug() << pos;
             if(pos > -1)
             {
                 QStringList strlist=values.split(QRegExp("\"*\" *,"));
                 for(int i=0;i<strlist.size();i++)
                 {
                     QString qtemp = strlist.at(i);
                     QStringList qstrlist=qtemp.split(QRegExp("\"*\""));
                     if(qstrlist.size()>=2)
                     {
                        QString v = qstrlist.at(1);
                        if(v.trimmed().section("\"",0,1).toLower() == "x")
                        {
                            dim++;

                        }else if(v.trimmed().section("\"",0,1).toLower() == "y")
                        {
                            dim++;

                        }else if(v.trimmed().section("\"",0,1).toLower() == "z")
                        {
                            dim++;
                        }else
                        {
                            value_n++;
                            value_name.append(v.trimmed().section("\"",0,1).toLower());
                        }

                     }else
                     {
                        return 0;
                     }
                     //qDebug()<<qtemp.size() <<qstrlist<<qstrlist.at(1).section("\"",0);
                 }
                // qDebug()<<"reg:"<<strlist.at(0)<<" "<<strlist.at(1);
                 return 1;
             }else{
                 return 0;
             }

        }

    }else{
        return 0;
    }
}


int Read_Tec::read_zones(QTextStream &in)
{
    QString line = in.readLine();
    if(line.trimmed()!= NULL){

       if(line.trimmed().startsWith("ZONE"))
       {
         // qDebug()<<line.split("\"").size()<<"111"<<line.split("\"").at(2).trimmed();
          if(line.split("\"").size() > 0)
          {
             zone_name = line.split("\"").at(1).trimmed();

              if(line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).size() > 4)
              {
                  if(line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).size() == 5)
                  {
//                     QString NE_t =line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).at(4).trimmed();
//                     qDebug()<<NE_t.section("=",0,0)<<NE_t.section("=",1,1);
//                     if(NE_t.section("=",0,0).trimmed().toUpper() == "N")
//                     {
//                         N = NE_t.section("=",1,1).trimmed().toInt();
//                         QString ELine = in.readLine();
//                     }else
//                     {

//                     }
                  }else if(line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).size() == 6)
                  {
                      QString NE_t =line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).at(4).trimmed();
                      if(NE_t.section("=",0,0).trimmed().toUpper() == "N")
                      {
                            N = NE_t.section("=",1,1).trimmed().toInt();

                      }else if(NE_t.section("=",0,0).trimmed().toUpper() == "E")
                      {
                            E  = NE_t.section("=",1,1).trimmed().toInt();
                      }else{
                          return 0;
                      }
                      qDebug()<<line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).at(5).trimmed();
                      NE_t =line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).at(5).trimmed();
                      if(NE_t.section("=",0,0).trimmed().toUpper() == "N")
                      {
                            N = NE_t.section("=",1,1).trimmed().toInt();

                      }else if(NE_t.section("=",0,0).trimmed().toUpper() == "E")
                      {

                            E  = NE_t.section("=",1,1).trimmed().toInt();
                      }else{
                          return 0;
                      }
                  }

              }
              //qDebug()<< line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).size()<<line.split("\"").at(2).trimmed().split(QRegExp(",*=*,")).at(4) ;
          }else
          {
              return 0;
          }
       }else
       {
           return 0;
       }
    }else
    {
        return 0;
    }
    return 1;
}


int Read_Tec::read_points(QTextStream &in)
{
   int linenumber = 0;
   int point_number = 0;
   int t_p_n = 0;
   int next_dn = 0;
   QList<float> vv;
   int vn = 0;
   QMap<QString,QList<float>> store_v;
   for(int i=0;i<value_n;i++)
   {
       QList<float> value;
       store_v.insert(value_name.at(i),value);
   }
   while(point_number < N * (dim + value_n))
   {
       QString line = in.readLine();
       QStringList  temp = line.trimmed().simplified().split(" ");
       if(dim == 2)
       {

           for(int i=0;i<temp.size();i++)
           {
               if(next_dn == 0)
               {
                   this->tec_data->Coord_x.append(temp.at(i).trimmed().toFloat());
                   point_number++;

               }
               else if(next_dn == 1)
               {
                  this->tec_data->Coord_y.append(temp.at(i).trimmed().toFloat());
                  point_number++;
               }


               else if(next_dn > 1)
               {

                   vv.push_back(temp.at(i).trimmed().toFloat());
                   point_number++;
                   vn++;
                   if(vn == N)
                   {
                       qDebug()<<next_dn<<point_number;
                        QString key = value_name.at(next_dn - dim);
                        this->tec_data->values.insert(key,vv);
                   }
               }
           }


       }else if(dim == 3)
       {
          for(int i=0;i<temp.size();i++)
          {
              if(next_dn == 0)
              {
                  this->tec_data->Coord_x.append(temp.at(i).trimmed().toFloat());
                  point_number++;

              }
              else if(next_dn == 1)
              {
                 this->tec_data->Coord_y.append(temp.at(i).trimmed().toFloat());
                 point_number++;
              }
              else if(next_dn == 2)
              {
                   this->tec_data->Coord_z.append(temp.at(i).trimmed().toFloat());
                   point_number++;
              }

              else if(next_dn > 2)
              {

                  vv.push_back(temp.at(i).trimmed().toFloat());
                  point_number++;
                  vn++;
                  if(vn == N)
                  {
                      qDebug()<<next_dn<<point_number;
                       QString key = value_name.at(next_dn - dim);
                       this->tec_data->values.insert(key,vv);
                  }
              }
          }

       }

       //point_number += temp.size();
       next_dn = point_number / N;
//       if(next_dn == 0)
//       {
//            qDebug()<<next_dn<<point_number<<point_number % N << N;
//       }

       if(point_number >=N * (dim + value_n))
       {
           break;
       }
       linenumber ++;
       //qDebug()<<temp<<"\r\n"<<linenumber << N * (dim + value_n)<<point_number;
   }

   //this->tec_data->values = store_v;
   return 1;
}



int Read_Tec::read_cells(QTextStream &in)
{
    int linenumber = 0;
    while(linenumber < 2 *E)
    {
        QString firstline = in.readLine().simplified();
        QString secondline = in.readLine().simplified();
        QStringList first_result = firstline.split(" ");
        QStringList second_result = secondline.split(" ");
        if(first_result.size()+second_result.size() != 8)
        {
            return 0;
        }


        QList<int> cell_list;
        for(int i=0;i<first_result.size();i++)
        {
            if(cell_list.size()>1)
            {
                if(cell_list.at(cell_list.size()-1) !=  first_result.at(i).toInt())
                {
                     cell_list.push_back(first_result.at(i).toInt());
                }
            }else{
                   cell_list.push_back(first_result.at(i).toInt());
            }
        }
        for(int i=0;i<second_result.size();i++)
        {


            if(cell_list.size()>1)
            {
                if(cell_list.at(cell_list.size()-1) !=  second_result.at(i).toInt())
                {
                     cell_list.push_back(second_result.at(i).toInt());
                }
            }else{
                   cell_list.push_back(second_result.at(i).toInt());
            }
        }
        this->tec_data->Cell.push_back(cell_list);
//        if(linenumber == 0)
//        {

//            qDebug()<<first_result<<second_result;
//            for(int i=0;i<cell_list.size();i++)
//            {
//                qDebug()<<cell_list.at(i);
//            }
//        }
        linenumber += 2;


    }
    return 1;
}


