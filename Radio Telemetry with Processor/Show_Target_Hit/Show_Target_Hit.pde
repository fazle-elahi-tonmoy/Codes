import processing.serial.*;

Serial myPort;
String data;
float[] values = new float[4];

ArrayList<Shot> shots = new ArrayList<Shot>();  // store all shots
PVector center;

void setup() {
  size(800, 600);
  center = new PVector(width/2, height/2);
  
  // Uncomment when Arduino is ready
   myPort = new Serial(this, "COM25", 9600); 
}
 
void draw() {
  background(0);
  drawTarget();

  // Read serial data (simulated if no Arduino)
  if (myPort != null && myPort.available() > 0) {
    data = myPort.readStringUntil('\n');
    if (data != null) {
      String[] parts = split(trim(data), ',');
      if (parts.length == 4) {
        for (int i = 0; i < 4; i++) values[i] = float(parts[i]);
        addShot();
      }
    }
  }
  
  // For demo: add random shots every 2 sec
  if (frameCount % 120 == 0 && myPort == null) {
    addShot();
  }

  // Draw all shots
  for (int i=0; i<shots.size(); i++) {
    shots.get(i).display(i+1);
  }

  // Draw scoreboard
  drawScoreboard();
}

void drawTarget() {
  stroke(255);
  noFill();
  for (int r = 50; r <= 400; r += 50) {
    ellipse(center.x, center.y, r, r);
  }
}

void addShot() {
  // Replace with trilateration from values[]
  float x = random(center.x-100, center.x+100);
  float y = random(center.y-100, center.y+100);
  shots.add(new Shot(x, y));
}

void drawScoreboard() {
  fill(255);
  textSize(14);
  text("Shot  Score", 620, 40);
  
  int total = 0;
  for (int i=0; i<shots.size(); i++) {
    int score = shots.get(i).score;
    text(nf(i+1,2) + "    " + score, 620, 60 + i*20);
    total += score;
  }
  text("TOTAL: " + total, 620, 60 + shots.size()*20);
}

class Shot {
  float x, y;
  int score;
  
  Shot(float x, float y) {
    this.x = x;
    this.y = y;
    this.score = calcScore();
  }
  
  int calcScore() {
    float d = dist(x, y, center.x, center.y);
    if (d < 50) return 10;
    else if (d < 100) return 9;
    else if (d < 150) return 8;
    else if (d < 200) return 7;
    else if (d < 250) return 6;
    else if (d < 300) return 5;
    else if (d < 350) return 4;
    else if (d < 400) return 3;
    else return 0;
  }
  
  void display(int num) {
    fill(255,0,0);
    ellipse(x, y, 12, 12);
    fill(255);
    textSize(12);
    text(num, x+10, y);
  }
}
