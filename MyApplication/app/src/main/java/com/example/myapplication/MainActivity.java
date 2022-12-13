package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.github.angads25.toggle.interfaces.OnToggledListener;
import com.github.angads25.toggle.model.ToggleableView;
import com.github.angads25.toggle.widget.LabeledSwitch;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    MQTTHelper mqttHelper;
    TextView txtTemp, txtHumi, txtLig, txtAI, txtBtnState;
    LabeledSwitch btn1, btn2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        txtTemp = findViewById(R.id.txtTemperature);
        txtHumi = findViewById(R.id.txtHumidity);
        txtLig = findViewById(R.id.txtLight);
        txtAI = findViewById(R.id.txtAI);
        btn1 = findViewById(R.id.buttonLED1);
        btn2 = findViewById(R.id.buttonLED2);
        txtAI = findViewById(R.id.txtAI);
        btn1.setEnabled(false);
        btn2.setEnabled(false);
        txtBtnState = findViewById(R.id.txtCnt);
        btn1.setOnToggledListener(new OnToggledListener() {
            @Override
            public void onSwitched(ToggleableView toggleableView, boolean isOn) {
                if(isOn == true){
                    sendDataMQTT("thoriumrabbit02/feeds/nutnhan1","1");
                }else{
                    sendDataMQTT("thoriumrabbit02/feeds/nutnhan1","0");
                }
            }
        });
        btn2.setOnToggledListener(new OnToggledListener() {
            @Override
            public void onSwitched(ToggleableView toggleableView, boolean isOn) {
                if(isOn == true){
                    sendDataMQTT("thoriumrabbit02/feeds/nutnhan2","3");
                }else{
                    sendDataMQTT("thoriumrabbit02/feeds/nutnhan2","2");
                }
            }
        });
        startMQTT();
    }

    public void sendDataMQTT(String topic, String value)
    {
        MqttMessage msg = new MqttMessage();
        msg.setId(1234);
        msg.setQos(0);
        msg.setRetained(false);

        byte[] b = value.getBytes(Charset.forName("UTF-8"));
        msg.setPayload(b);

        try {
            mqttHelper.mqttAndroidClient.publish(topic, msg);
        } catch (MqttException e){
        }
    }
    public void startMQTT(){
        mqttHelper = new MQTTHelper(this);
        mqttHelper.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean reconnect, String serverURI) {
                txtBtnState.setText("Connected");
                btn1.setEnabled(true);
                btn2.setEnabled(true);
            }

            @Override
            public void connectionLost(Throwable cause) {
                txtBtnState.setText("Disconnected");
                btn1.setEnabled(false);
                btn2.setEnabled(false);
            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                Log.d("TEST", topic + "***" + message.toString());
                if(topic.contains("tempsensor")){
                    txtTemp.setText(message.toString() + "°C");
                }
                else if (topic.contains("humisensor")){
                    txtHumi.setText(message.toString() + "%");
                }
                else if (topic.contains("lightsensor")){
                    txtLig.setText(message.toString() + " LUX");
                }
                else if(topic.contains("visiondetection")){
                    txtAI.setText(message.toString());
                }
                else if(topic.contains("nutnhan1")){
                    if(message.toString().equals("1")){
                        btn1.setOn(true);
                    }
                    else{
                        btn1.setOn(false);
                    }
                }else if(topic.contains("nutnhan2")){
                    if(message.toString().equals("3")){
                        btn2.setOn(true);
                    }
                    else{
                        btn2.setOn(false);
                    }
                }
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });
    }


}