#ifndef AUTOMATEDINPUTDATA_H
#define AUTOMATEDINPUTDATA_H


class AutomatedInputData
{
    public:
        AutomatedInputData( int _userId , float _x , float _y , float _timeOffset )
        {
            userId = _userId ;
            x = _x ;
            y = _y ;
            timeOffset = _timeOffset ;
        }
        virtual ~AutomatedInputData() {}

        int userId;
        float x , y ;
        float timeOffset ;

    protected:
    private:
};

#endif // AUTOMATEDINPUTDATA_H
