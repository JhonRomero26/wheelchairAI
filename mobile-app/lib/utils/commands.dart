enum MovementCommands {
  forward('mf'),
  backward('mb'),
  left('ml3'),
  right('mr3'),
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

enum ModeCommands {
  homeOn('md=hm1'),
  homeOff('md=hm0');

  const ModeCommands(this.value);
  final String value;
}

enum CorrectionCommands {
  engine("ec="),
  acceleration("ac=");

  const CorrectionCommands(this.value);
  final String value;
}
