/*
  This is a library written for the AS726X Spectral Sensor (Visible or IR) with I2C firmware
  specially loaded. SparkFun sells these at its website: www.sparkfun.com

  Written by Nathan Seidle & Andrew England @ SparkFun Electronics, July 12th, 2017

  https://github.com/sparkfun/Qwiic_Spectral_Sensor_AS726X

  Do you like this library? Help support SparkFun. Buy a board!

  Development environment specifics:
  Arduino IDE 1.8.1

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "AS726X.h"
AS726X sensor;//Creates the sensor object

byte GAIN = 3;
byte MEASUREMENT_MODE = 3;
int led = -1;


void setup() {
  Wire.begin();
  Serial.begin(115200);
  sensor.begin(Wire, GAIN, MEASUREMENT_MODE);

  sensor.setBulbCurrent(3);
  sensor.setGain(3);
  sensor.setIntegrationTime(187);
}

void loop() {

  while (Serial.available() == false)
  {
  }              //Do nothing while we wait for user to press a key
  Serial.read(); //Throw away the user's button
  led++;
  
  sensor.takeMeasurements();

  //Near IR readings
  //Serial.print(",");
  Serial.print(sensor.getCalibratedR(), 2);
  Serial.print(",");
  Serial.print(sensor.getCalibratedS(), 2);
  Serial.print(",");
  Serial.print(sensor.getCalibratedT(), 2);
  Serial.print(",");
  Serial.print(sensor.getCalibratedU(), 2);
  Serial.print(",");
  Serial.print(sensor.getCalibratedV(), 2);
  Serial.print(",");
  Serial.print(sensor.getCalibratedW(), 2);

  Serial.println();
}
