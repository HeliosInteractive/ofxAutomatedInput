
/*
    Created by Ben McChesney
    @ Helios Interactive

    301 8th Street, STE 250
    San Francisco , CA

    5/3/2013
*/

#include "ofxAutomatedInput.h"

ofxAutomatedInput::ofxAutomatedInput()
{
    //ctor
    startRecordingTime = -3 ;
    playbackIndex = -3 ;
    maxLoopTime = 0.0f ;
    loopOffsetTime = 0.0f ;
    startPlaybackTime = 0.0f ;
}

ofxAutomatedInput::~ofxAutomatedInput()
{
    //dtor
}

 void ofxAutomatedInput::update( )
 {

    if ( getIsPlaying() == true )
    {
        float adjustedTime = (ofGetElapsedTimef()-startPlaybackTime) + loopOffsetTime ;
        if ( adjustedTime > maxLoopTime )
            loopOffsetTime += -maxLoopTime ;

        int prevIndex = playbackIndex ;
        for ( int i = 0 ; i < inputData.size() ; i++ )
        {
            if ( adjustedTime > inputData[ i ].timeOffset )
            {
                playbackIndex = i ;
            }
        }
        if ( prevIndex != playbackIndex )
        {
                cout << "EVENT @ " << ofGetElapsedTimef() << " [" << playbackIndex << "] " << endl ;
                ofNotifyEvent( AUTOMATED_INPUT , inputData[ playbackIndex ] ) ;
        }
    }
 }

string ofxAutomatedInput::getDebugString( )
{
    stringstream ss ;
    ss << " @ input : " << playbackIndex << " / " << (inputData.size()-1) << " | # loops: " << floor( abs( loopOffsetTime / maxLoopTime )) ;
    return ss.str() ;
}

void ofxAutomatedInput::draw ( )
{
    ofEnableAlphaBlending() ;
    if ( inputData.size() > 0 )
    {
        ofPushStyle() ;
            ofSetColor ( 255 , 80 ) ;
            ofSetLineWidth( 3 ) ;

            for ( int i = 0 ; i < inputData.size() ; i++ )
            {
                ofCircle( inputData[ i ].x , inputData[ i ].y , 8 ) ;
            }
        ofPopStyle() ;

        if ( getIsPlaying() == true )
        {
            float adjustedTime = ofGetElapsedTimef() + loopOffsetTime ;
            if ( abs( adjustedTime - inputData[ playbackIndex ].timeOffset ) < 0.15f )
            {
                ofSetColor( 15 , 255 , 15 , 255 ) ;
                ofCircle( inputData[ playbackIndex ].x , inputData[ playbackIndex ].y , 14 ) ;
            }
            else
            {
                ofSetColor( 15 , 255 , 15 , 90 ) ;
                ofCircle( inputData[ playbackIndex ].x , inputData[ playbackIndex ].y , 10 ) ;
            }
        }
    }
}

void ofxAutomatedInput::reset( )
{
    xml.clear() ;
    inputData.clear() ;
    loopOffsetTime = 0.0f ;
}

void ofxAutomatedInput::togglePlayback( )
{
    if ( getIsPlaying() == false )
    {
        if ( inputData.size() > 0 )
        {
            startPlaybackTime = ofGetElapsedTimef() ;
            playbackIndex = 0 ;
            ofNotifyEvent( AUTOMATED_INPUT , inputData[ playbackIndex ] ) ;
        }
    }
    else
    {
        playbackIndex = -2 ;
        startPlaybackTime = 0.0f ;
    }

}

void ofxAutomatedInput::toggleRecording( )
{
    if ( startRecordingTime < 0 )
    {
        startRecordingTime = ofGetElapsedTimef() ;
        ofLog( OF_LOG_VERBOSE , "ofxAutomatedInput::toggleRecording now RECORDING" ) ;
    }
    else
    {
        startRecordingTime = -3 ;
        ofLog( OF_LOG_VERBOSE , "ofxAutomatedInput::toggleRecording now DONE recording" ) ;
    }
}

void ofxAutomatedInput::addInput( float x , float y , int userId )
{
    if ( getIsRecording() == true )
        inputData.push_back( AutomatedInputData( userId , x , y , ofGetElapsedTimef() - startRecordingTime ) ) ;
}

void ofxAutomatedInput::loadXml( string path )
{
    bool bLoadResult = xml.loadFile( path ) ;
    if( bLoadResult == false )
    {
        ofLog( OF_LOG_VERBOSE , " XML @ '" + path + "' did not load ! " ) ;
    }

    int numInputPoints = xml.getNumTags( "inputData" ) ;
    for ( int i = 0 ; i < numInputPoints ; i++ )
    {
        //Push Into and Populate vector
        xml.pushTag( "inputData" , i ) ;
            int userId = xml.getValue( "userId" , 0 ) ;
            float x = xml.getValue( "x" , 0.0f ) ;
            float y = xml.getValue( "y" , 0.0f ) ;
            float timeOffset = xml.getValue( "timeOffset" , 0.0f ) ;
            inputData.push_back( AutomatedInputData( userId , x , y , timeOffset ) ) ;
        xml.popTag( ) ;
    }

    if ( numInputPoints > 0 )
        maxLoopTime = inputData[ (inputData.size() -1 ) ].timeOffset + 3.0f ;

}

void ofxAutomatedInput::saveXml( string path )
{
    xml.clear() ;
    for ( int i = 0 ; i < inputData.size() ; i++ )
    {
        int tagIndex = xml.addTag( "inputData" ) ;
        xml.pushTag( "inputData" , tagIndex ) ;

            //Push Into and Populate Tagsss
            xml.setValue( "userId" , inputData[ i ].userId ) ;
            xml.setValue( "x" , inputData[ i ].x ) ;
            xml.setValue( "y" , inputData[ i ].y ) ;
            xml.setValue( "timeOffset" , inputData[ i ].timeOffset ) ;

        xml.popTag( ) ;
    }

    xml.saveFile( path ) ;
}

bool ofxAutomatedInput::getIsRecording()
{
    if ( startRecordingTime < 0 )
        return false ;
    else
        return true ;
}

bool ofxAutomatedInput::getIsPlaying()
{
    if ( playbackIndex < 0 )
        return false ;
    else
        return true ;
}



