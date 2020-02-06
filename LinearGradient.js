import React from 'react';
import { requireNativeComponent } from 'react-native';

const ShadowLinearGradientView = requireNativeComponent('ShadowLinearGradientView');

export default class LinearGradient extends React.PureComponent {
  render() {
    return <ShadowLinearGradientView {...this.props} />;
  }
}