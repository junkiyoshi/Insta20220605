#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	float R = 250;
	float r = R * 0.25;
	float u_span = 15;
	float threshold = 0.55;

	for (float r = 60; r < 90; r += 10) {

		for (float u = 0; u < 360; u += u_span) {

			for (float v = 0; v < 360; v += 1.5) {

				auto noise_value = ofNoise(glm::vec4(this->make_point(R, r * 10, u, v) * 0.0015, ofGetFrameNum() * 0.008));

				if (noise_value < threshold) {

					continue;
				}

				auto prev_noise_value = ofNoise(glm::vec4(this->make_point(R, r * 10, u, v - 1.5) * 0.0015, ofGetFrameNum() * 0.008));
				auto next_noise_value = ofNoise(glm::vec4(this->make_point(R, r * 10, u, v + 1.5) * 0.0015, ofGetFrameNum() * 0.008));

				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(this->make_point(R, r, u - u_span * 0.5 + 1, v - 1.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, u + u_span * 0.5 - 1, v - 1.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, u + u_span * 0.5 - 1, v + 1.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, u - u_span * 0.5 + 1, v + 1.5)));

				vertices.push_back(glm::vec3(this->make_point(R, r - 9, u - u_span * 0.5 + 1, v - 1.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r - 9, u + u_span * 0.5 - 1, v - 1.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r - 9, u + u_span * 0.5 - 1, v + 1.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r - 9, u - u_span * 0.5 + 1, v + 1.5)));

				this->face.addVertices(vertices);
				this->line.addVertices(vertices);

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(ofColor(0));
					this->line.addColor(ofColor(255));
				}

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);
				this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);

				this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 8);
				this->face.addIndex(this->face.getNumVertices() - 7); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 8);

				this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 5);
				this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 8);

				this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 6);
				this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 7);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 4);
				this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);

				this->line.addIndex(this->line.getNumVertices() - 5); this->line.addIndex(this->line.getNumVertices() - 8);
				this->line.addIndex(this->line.getNumVertices() - 6); this->line.addIndex(this->line.getNumVertices() - 7);

				if (next_noise_value < threshold) {

					this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 5);
					this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 2);

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addIndex(this->line.getNumVertices() - 5); this->line.addIndex(this->line.getNumVertices() - 6);

					this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 6);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 5);
				}

				if (prev_noise_value < threshold) {

					this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 7);
					this->face.addIndex(this->face.getNumVertices() - 7); this->face.addIndex(this->face.getNumVertices() - 8); this->face.addIndex(this->face.getNumVertices() - 4);

					this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);
					this->line.addIndex(this->line.getNumVertices() - 7); this->line.addIndex(this->line.getNumVertices() - 8);

					this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 7);
					this->line.addIndex(this->line.getNumVertices() - 4); this->line.addIndex(this->line.getNumVertices() - 8);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->line.drawWireframe();
	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}