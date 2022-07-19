/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("Peep:RotStage");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	ofSeedRandom();
	
	ofEnableAntiAliasing();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD
	
	/********************
	********************/
	setup_udp();
	
	/********************
	********************/
	gui.setup();
	gui.add(gui__th_DetectBlack.setup("th_DetectBlack", 500, 10, 1000));
	gui.add(gui__t_1Round_sec_SafetyGuard.setup("t_1Round", 32, 5, 60));
}

/******************************
******************************/
void ofApp::setup_udp(){
	/********************
	********************/
	{
		ofxUDPSettings settings;
		// settings.sendTo("127.0.0.1", 12345);
		settings.sendTo("10.0.0.6", 12345);
		settings.blocking = false;
		
		udp_Send.Setup(settings);
	}
	
	/********************
	********************/
	{
		ofxUDPSettings settings;
		settings.receiveOn(12345);
		settings.blocking = false;
		
		udp_Receive.Setup(settings);
	}
}

/******************************
******************************/
void ofApp::update(){
	char udpMessage[UDP_BUF_SIZE];
	udp_Receive.Receive(udpMessage, UDP_BUF_SIZE);
	string message=udpMessage;
	
	if(message!=""){
		int counter = 0;
		do{
			/********************
			********************/
			// printf("%s\n", message.c_str());
			// printf("> %d th message\n", counter);
			counter++;
			
			vector<string> strMessages = ofSplitString(message, "[p]");
			/*
			for(int i = 0; i < strMessages.size(); i++){
				printf("%s\n", strMessages[i].c_str());
			}
			*/
			
			if(2 <= strMessages.size()){
				if(strMessages[0] == "RotStage"){
					if(strMessages[1] == "Beat"){
						c_Beat++;
					}else if( (strMessages[0] == "RotStage") && (strMessages[1] == "Meas") ){
						if(3 <= strMessages.size()){
							printf("MeasLev = %d\n", atoi(strMessages[2].c_str()));
							fflush(stdout);
						}
					}else if( (strMessages[0] == "RotStage") && (strMessages[1] == "Succeeded") ){
						c_Succeeded++;
						if(4 <= strMessages.size()){
							printf( "Succeeded : %d [ms], LastBlackLevs = %s\n", atoi(strMessages[2].c_str()), strMessages[3].c_str() );
							fflush(stdout);
						}
					}else if( (strMessages[0] == "RotStage") && (strMessages[1] == "OverRun") ){
						c_OverRun++;
						if(3 <= strMessages.size()){
							printf("OverRun : %d [ms]\n", atoi(strMessages[2].c_str()));
							fflush(stdout);
						}
					}
				}
			}
			
			/********************
			********************/
			udp_Receive.Receive(udpMessage, UDP_BUF_SIZE);
			message=udpMessage;
		}while(message!="");
	}
}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(40);
	
	gui.draw();
	
	/*
	printf("c_Beats = %d\r", c_Beat);
	fflush(stdout);
	*/
}

/******************************
******************************/
void ofApp::sendUdpTo_RotStage__action(){
	char buf[100];
	sprintf( buf, "%d|%d", int(gui__th_DetectBlack), int(gui__t_1Round_sec_SafetyGuard) );
	
	string message="";
	message += "oF|action|";
	message += buf;
	
	udp_Send.Send(message.c_str(),message.length());
}

/******************************
******************************/
void ofApp::sendUdpTo_RotStage(string message){
	udp_Send.Send(message.c_str(),message.length());
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
			sendUdpTo_RotStage("oF|AC_ON|0|0");
			printf("> send command = AC_ON\n");
			break;
			
		case '1':
			sendUdpTo_RotStage("oF|AC_OFF|0|0");
			printf("> send command = AC_OFF\n");
			break;
			
		case 'm':
			sendUdpTo_RotStage("oF|Meas|0|0");
			printf("> send command = Meas\n");
			break;
			
		case ' ':
			sendUdpTo_RotStage__action();
			printf("> send command = action\n");
			break;
			
		case 'd':
			printf("c_Beat = %d\n", c_Beat);
			if(0 < c_Succeeded + c_OverRun){
				printf("(OK, NG) = (%d, %d) / %d\n", c_Succeeded, c_OverRun, c_Succeeded + c_OverRun);
			}
			fflush(stdout);
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
