#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	ofIcoSpherePrimitive ico_sphere = ofIcoSpherePrimitive(300, 2);
	vector<ofMeshFace> triangles = ico_sphere.getMesh().getUniqueFaces();
	for (int i = 0; i < triangles.size(); i++) {

		ofPoint average = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		this->locations.push_back(average);
	}

	for (int i = 0; i < this->locations.size(); i++) {

		vector<ofPoint> next_point = vector<ofPoint>();
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j || next_point.size() >= 3) { continue; }

			float distance = this->locations[i].distance(this->locations[j]);
			if (distance < 60) {

				next_point.push_back(this->locations[j]);
			}
		}

		this->next_points.push_back(next_point);
	}

}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	for (int location_index = 0; location_index < this->locations.size(); location_index++) {

		ofPoint location = this->locations[location_index];
		float location_noise = ofNoise(location.x * 0.03, location.y * 0.03, ofGetFrameNum() * 0.005);

		for (int next_index = 0; next_index < this->next_points[location_index].size(); next_index++) {

			ofPoint next_point = this->next_points[location_index][next_index];
			ofPoint distance = next_point - location;
			distance = distance.normalize() * ofMap(location_noise, 0, 1, 0, distance.length() * 0.65);

			ofDrawLine(location, location + distance);
		}
	}

	this->cam.end();

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}