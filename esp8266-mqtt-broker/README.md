# ESP8266 MQTT Broker

Sample on how to connect to a MQTT broker from ESP8266 and publish/subscribe on topics.

## Configure local MQTT broker

To test this sample I've configured the [Mosquitto](https://mosquitto.org/) broker in a [docker container](https://www.docker.com/) on my laptop.

```bash
$ docker pull eclipse-mosquitto
$ docker run -it --rm --name mosquitto -p 1883:1883 eclipse-mosquitto
```

You can test your container by subscribing to a topic and publishing something to it:

1. Have installed a mosquitto client in your machine.

   ```bash
   sudo apt install mosquitto-clients
   ```

2. Subscribe to a topic in a terminal.

   ```bash
   $ mosquitto_sub -t test_topic
   ```

3. Publish a sample message using another terminal.

   ```bash
   $ mosquitto_pub -t test_topic -m 'sample message'
   ```

4. Check your subscriber terminal, it should have the published message printed.
