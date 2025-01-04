void protectionLimitCheckFunc(int testSample, int minLimit, int maxLimit) {

  if (testSample < minLimit or testSample > maxLimit) {

    onOffState = 0;
    LoadOnOffControlFunc(onOffState);

  }

}
