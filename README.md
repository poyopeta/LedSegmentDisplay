# LedSegmentDisplay
a personal library for 4 digit display with 7 segment LEDs

## Current State
正数の表示はできるが、Pro Microのint型が16ビットなので32767以上の入力は負として渡される。
そこでマイナスにも対応した表示をできるようにしたい。
小数も表示したい。
