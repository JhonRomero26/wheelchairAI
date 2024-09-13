enum MovementCommands {
  forward('mf'),
  backward('mb'),
  left('ml'),
  right('mr'),
  leftOff('l0'),
  rightOff('r0'),
  rotateLeft('rl'),
  rotateRigh('rr'),
  stop('ms');

  const MovementCommands(this.value);
  final String value;
}

enum SpeedCommands {
  slow('sv'),
  normal('nv'),
  fast('fv');

  const SpeedCommands(this.value);
  final String value;
}

enum ActionCommands {
  turnOn('turnOn'),
  turnOff('turnOff'),
  caxon('claxon');

  const ActionCommands(this.value);
  final String value;
}

enum CorrectionCommands {
  engine("ec="),
  acceleration("ac=");

  const CorrectionCommands(this.value);
  final String value;
}
