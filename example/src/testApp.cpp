#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){
    autoInput.update() ;
}

//--------------------------------------------------------------
void testApp::draw(){

    autoInput.draw( ) ;
    stringstream ss ;
    string boolString ;
    if ( autoInput.getIsRecording() == true )
        boolString = " true " ;
    else
        boolString = " false " ;

    string playingString ;
    if ( autoInput.getIsPlaying() == true )
        playingString = " true " ;
    else
        playingString = " false " ;

    ss << " (T) - Is it recording ? " << boolString << endl ;
    ss << " (P) - Is it playing ? " << playingString << endl ;
    ss << " (R) - reset data" << endl ;
    ss << " (S) - save data to XML" << endl ;
    ss << " (L) - load data from XML" << endl ;
    ss << " # inputs : " << autoInput.inputData.size() << endl ;

    ofDrawBitmapStringHighlight( ss.str() , 15 , 25 ) ;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    ofFileDialogResult result ;
    switch ( key )
    {
        case 't' :
        case 'T':
            autoInput.toggleRecording() ;
            break ;

        case 'r' :
        case 'R':
            autoInput.reset() ;
            break ;

        case 's' :
        case 'S':
            result = ofSystemSaveDialog( "data.xml" , "Export Input Data as XML" ) ;
            if ( result.bSuccess )
                autoInput.saveXml( result.getPath() ) ;
            break ;

        case 'l':
        case 'L':
            result = ofSystemLoadDialog( "Select an input data XML" , false ) ;
            if ( result.bSuccess )
                autoInput.loadXml( result.getPath() ) ;
            break ;

        case 'p':
        case 'P':
            autoInput.togglePlayback() ;
            break ;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    autoInput.addInput( x , y , 0 ) ;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
