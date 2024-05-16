import * as React from 'react';

import { StyleSheet, Text, View } from 'react-native';
import { FaceDetectorView } from 'vision-camera-face-detector';

export default function App() {
  return (
    <View style={styles.container}>
      <Text>AEEEEEEEEEEE</Text>
      <FaceDetectorView
        style={{ borderWidth: 1, width: 100, minHeight: 100 }}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
