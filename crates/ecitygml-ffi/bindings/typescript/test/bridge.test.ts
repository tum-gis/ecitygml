import assert from 'node:assert/strict';
import { test } from 'node:test';

import { Bridge, BridgePart, Tunnel } from '../lib/index.mjs';
import { features, readMember } from './helpers.ts';

test('bridge and bridge part', () => {
    const cityModel = readMember(`<cityObjectMember>
    <brid:Bridge gml:id="bridge_1">
      <brid:class>1000</brid:class>
      <brid:isMovable>true</brid:isMovable>
      <brid:bridgePart><brid:BridgePart gml:id="bridge_part_1"><brid:isMovable>false</brid:isMovable></brid:BridgePart></brid:bridgePart>
    </brid:Bridge>
  </cityObjectMember>
</CityModel>
`);
    const all = [...features(cityModel.iterFeatures())];
    const bridge = all.map((f) => Bridge.tryFrom(f)).find((b) => b !== null);
    assert.ok(bridge);
    assert.equal(bridge.class_()?.value(), '1000');
    assert.equal(bridge.isMovable(), true);
    const part = bridge.bridgeParts().next().value?.object();
    assert.equal(part?.featureId().asStr(), 'bridge_part_1');
    assert.equal(part?.isMovable(), false);
    assert.equal(all.map((f) => BridgePart.tryFrom(f)).filter((p) => p !== null).length, 1);
});

test('tunnel and tunnel part', () => {
    const cityModel = readMember(`<cityObjectMember>
    <tun:Tunnel gml:id="tunnel_1">
      <tun:function>1010</tun:function>
      <tun:tunnelPart><tun:TunnelPart gml:id="tunnel_part_1"><tun:function>1030</tun:function></tun:TunnelPart></tun:tunnelPart>
    </tun:Tunnel>
  </cityObjectMember>
</CityModel>
`);
    const tunnel = [...features(cityModel.iterFeatures())].map((f) => Tunnel.tryFrom(f)).find((t) => t !== null);
    assert.ok(tunnel);
    assert.equal(tunnel.functions().next().value?.value(), '1010');
    assert.equal(tunnel.tunnelParts().next().value?.object()?.functions().next().value?.value(), '1030');
});
