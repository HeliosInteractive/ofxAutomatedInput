#ifndef OFXAUTOMATEDINPUT_H
#define OFXAUTOMATEDINPUT_H

#include "ofMain.h"

/*
    Created by Ben McChesney
    @ Helios Interactive

    301 8th Street, STE 250
    San Francisco , CA

    5/3/2013
*/

#include "ofxXmlSettings.h"
#include "AutomatedInputData.h"


class ofxAutomatedInput
{
    public:
        ofxAutomatedInput();
        virtual ~ofxAutomatedInput();

        void update( ) ;
        void draw ( ) ;
        void toggleRecording( ) ;
        void togglePlayback( ) ;
        void loadXml( string path ) ;
        void saveXml( string path ) ;
        void reset( ) ;

        void addInput( float x , float y , int userId = 0 ) ;
        bool getIsRecording() ;
        bool getIsPlaying() ;

        string getDebugString( ) ;
        ofEvent<AutomatedInputData> AUTOMATED_INPUT ;

    protected:
    private:

        vector<AutomatedInputData> inputData ;

        int playbackIndex ;
        float maxLoopTime ;
        float loopOffsetTime ;
        float startPlaybackTime ;
        float startRecordingTime ;
        ofxXmlSettings xml ;
};

#endif // OFXAUTOMATEDINPUT_H
