# gr-spread

A port of [SashaNullptr/gr-fhss](https://github.com/SashaNullptr/gr-fhss) (originally by Paul David, 2014) to **GNU Radio 3.10** with pybind11 bindings.

The original module targeted GNU Radio 3.7/3.8 with SWIG bindings and no longer builds on modern GNU Radio installs. This fork:

- Migrates from SWIG to pybind11 (GR 3.10 requirement)
- Updates `boost::shared_ptr` and other deprecated APIs
- Restructures the directory layout to GR 3.10 conventions
- Provides working GRC YAML files for all four blocks
- Adds workarounds for known GR 3.10.1.1 cmake quirks (sndfile target, component ordering)

## Blocks included

| Block | Type | Purpose |
|---|---|---|
| `cpfsk_mod` | sync_interpolator | Binary CPFSK modulator |
| `cpfsk_demod` | sync_decimator | Binary CPFSK demodulator |
| `synthesizer` | sync_block | FHSS frequency hopper (TX side) |
| `rx_synthesizer` | sync_block | FHSS de-hopper with early-late tracking (RX side) |

The other blocks from the original repo (`framer`, `deframer`, `ds_spreader`, `ds_despreader`, `msg_source`, etc.) were not ported. PRs welcome if you need them.

## Requirements

- GNU Radio 3.10 (tested on 3.10.1.1)
- `gnuradio-dev`, `libsndfile1-dev`
- CMake 3.8+, C++17 compiler
- pybind11

On Debian/Ubuntu/PYNQ:

```bash
sudo apt install gnuradio-dev libsndfile1-dev cmake build-essential pybind11-dev
```

## Building

```bash
git clone https://github.com/<your-username>/gr-spread.git
cd gr-spread
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig
```

## Verify the install

```bash
python3 -c "from gnuradio import spread; print(dir(spread))"
```

Should list the four block names.

## Using in GNU Radio Companion

After install, launch `gnuradio-companion` and look for the **`[spread]`** category in the block library. If blocks don't appear, clear GRC's cache:

```bash
rm -rf ~/.cache/gnuradio
```



## Known issues on GR 3.10.1.1

Some early GR 3.10 versions (notably the version shipped on PYNQ images) have CMake quirks that prevent component-list `find_package(Gnuradio ... COMPONENTS ...)` from setting up imported targets. The root `CMakeLists.txt` works around this by calling `find_package` per component in dependency order. If you build against newer GR, you can revert that block to a single call.

## License

GPL-3.0-or-later. See `COPYING`.

Original work copyright 2014 Paul David <pudavid@vt.edu>.
Port to GNU Radio 3.10 copyright 2026 lakshmideep.

## References

- Paul David — original gr-fhss module
- SashaNullptr — GR 3.8 update
- This port — for getting it working on GR 3.10
