/**
 * Basic You.i RN app
 */
import React, { Component } from 'react';
import { AppRegistry, Image, StyleSheet, Text, View } from 'react-native';

import LinearGradient from './LinearGradient';

export default class YiReactApp extends Component {
  render() {
    return (
      <View style={styles.mainContainer}>
        <View style={styles.headerContainer}>
          <View
            focusable={true}
            accessible={true}
            accessibilityLabel='Lego!'
            accessibilityHint='A mighty pile of lego!'
            accessibilityRole='image'
          >
            <Image
              style={styles.lego}
              source={{ uri: 'res://drawable/default/lego.jpg' }}
            />
            <LinearGradient
              start={{ x: 0, y: 0.67 }}
              end={{ x: 0, y: 1 }}
              startColor={{ red: 38, green: 38, blue: 38, alpha: 0 }}
              endColor={{ red: 38, green: 38, blue: 38, alpha: 255 }}
            />
            <LinearGradient
              start={{ x: 1, y: 0 }}
              end={{ x: 0.15, y: 0 }}
              startColor={{ red: 38, green: 38, blue: 38, alpha: 0 }}
              endColor={{ red: 38, green: 38, blue: 38, alpha: 255 }}
            />
          </View>
          <View
            style={styles.logoContainer}
            accessible={true}
            accessibilityLabel='You.i TV!'
            accessibilityHint='Art and Science!'
            accessibilityRole='image'
          >
          <Image
              style={styles.logo}
              source={{ uri: 'res://drawable/default/youi_logo_red.png' }}
            />
          </View>
        </View>
        <View style={styles.bodyContainer} focusable={true} accessible={true}>
          <Text
            style={styles.headlineText}
            accessibilityLabel='Welcome to your first You I React Native app'
          >
            Welcome to your first You.i React Native app!
          </Text>
          <Text
            style={styles.bodyText}
          >
            For more information on where to go next visit
          </Text>
          <Text
            style={styles.bodyText}
            accessibilityLabel='https://developer dot you i dot tv'
          >
            https://developer.youi.tv
          </Text>
        </View>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  mainContainer: {
    backgroundColor: '#e6e7e7',
    flex: 1
  },
  headerContainer: {
    backgroundColor: '#262626',
    justifyContent: 'flex-end',
    alignItems: 'flex-end',
    flexDirection: 'row',
    flex: 2,
  },
  logoContainer: {
    width: '50%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    position: 'absolute', // We need to use flex box to properly align the image and gradients
    left: 0,              // so this content will need to be positioned absolutely.
    top: 0,
  },
  lego: {
    width: 480,  // Original image dimensions are 960x540
    height: '100%',
    resizeMode: 'stretch'
  },
  logo: {
    width: 128,  // Original image dimensions are 256x238
    height: 119,
    resizeMode: 'stretch'
  },
  bodyContainer: {
    alignItems: 'center',
    justifyContent: 'center',
    flex: 1
  },
  headlineText: {
    marginBottom: 10,
    color: '#333333',
    textAlign: 'center'
  },
  bodyText: {
    color: '#333333',
    textAlign: 'center'
  }
});

AppRegistry.registerComponent('YiReactApp', () => YiReactApp);
