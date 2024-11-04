#include "libbmp.h"
#include <math.h>
#include <stdio.h>
#include <sys/types.h>

#define SINCOS_WOBBLE 1
#define BASE_X 17920.00
#define BASE_Y 7168.00
#define BIOME_W 70
#define BIOME_H 48

int mod(int a, int b) {
	int c = a % b;
	if (c < 0) {
		c = c + b;
	}
	return c;
}

int SampleBiomeMapClampedWrapping(int x, int y) {
	return mod(x, 2) * 2 + mod(y, 2);
}

double sqrt312;
double sqrt336;

short MysteryBiomeDataArray[256] = {
    0x0097, 0x00a0, 0x0089, 0x005b, 0x005a, 0x000f, 0x0083, 0x000d, 0x00c9,
    0x005f, 0x0060, 0x0035, 0x00c2, 0x00e9, 0x0007, 0x00e1, 0x008c, 0x0024,
    0x0067, 0x001e, 0x0045, 0x008e, 0x0008, 0x0063, 0x0025, 0x00f0, 0x0015,
    0x000a, 0x0017, 0x00be, 0x0006, 0x0094, 0x00f7, 0x0078, 0x00ea, 0x004b,
    0x0000, 0x001a, 0x00c5, 0x003e, 0x005e, 0x00fc, 0x00db, 0x00cb, 0x0075,
    0x0023, 0x000b, 0x0020, 0x0039, 0x00b1, 0x0021, 0x0058, 0x00ed, 0x0095,
    0x0038, 0x0057, 0x00ae, 0x0014, 0x007d, 0x0088, 0x00ab, 0x00a8, 0x0044,
    0x00af, 0x004a, 0x00a5, 0x0047, 0x0086, 0x008b, 0x0030, 0x001b, 0x00a6,
    0x004d, 0x0092, 0x009e, 0x00e7, 0x0053, 0x006f, 0x00e5, 0x007a, 0x003c,
    0x00d3, 0x0085, 0x00e6, 0x00dc, 0x0069, 0x005c, 0x0029, 0x0037, 0x002e,
    0x00f5, 0x0028, 0x00f4, 0x0066, 0x008f, 0x0036, 0x0041, 0x0019, 0x003f,
    0x00a1, 0x0001, 0x00d8, 0x0050, 0x0049, 0x00d1, 0x004c, 0x0084, 0x00bb,
    0x00d0, 0x0059, 0x0012, 0x00a9, 0x00c8, 0x00c4, 0x0087, 0x0082, 0x0074,
    0x00bc, 0x009f, 0x0056, 0x00a4, 0x0064, 0x006d, 0x00c6, 0x00ad, 0x00ba,
    0x0003, 0x0040, 0x0034, 0x00d9, 0x00e2, 0x00fa, 0x007c, 0x007b, 0x0005,
    0x00ca, 0x0026, 0x0093, 0x0076, 0x007e, 0x00ff, 0x0052, 0x0055, 0x00d4,
    0x00cf, 0x00ce, 0x003b, 0x00e3, 0x002f, 0x0010, 0x003a, 0x0011, 0x00b6,
    0x00bd, 0x001c, 0x002a, 0x00df, 0x00b7, 0x00aa, 0x00d5, 0x0077, 0x00f8,
    0x0098, 0x0002, 0x002c, 0x009a, 0x00a3, 0x0046, 0x00dd, 0x0099, 0x0065,
    0x009b, 0x00a7, 0x002b, 0x00ac, 0x0009, 0x0081, 0x0016, 0x0027, 0x00fd,
    0x0013, 0x0062, 0x006c, 0x006e, 0x004f, 0x0071, 0x00e0, 0x00e8, 0x00b2,
    0x00b9, 0x0070, 0x0068, 0x00da, 0x00f6, 0x0061, 0x00e4, 0x00fb, 0x0022,
    0x00f2, 0x00c1, 0x00ee, 0x00d2, 0x0090, 0x000c, 0x00bf, 0x00b3, 0x00a2,
    0x00f1, 0x0051, 0x0033, 0x0091, 0x00eb, 0x00f9, 0x000e, 0x00ef, 0x006b,
    0x0031, 0x00c0, 0x00d6, 0x001f, 0x00b5, 0x00c7, 0x006a, 0x009d, 0x00b8,
    0x0054, 0x00cc, 0x00b0, 0x0073, 0x0079, 0x0032, 0x002d, 0x007f, 0x0004,
    0x0096, 0x00fe, 0x008a, 0x00ec, 0x00cd, 0x005d, 0x00de, 0x0072, 0x0043,
    0x001d, 0x0018, 0x0048, 0x00f3, 0x008d, 0x0080, 0x00c3, 0x004e, 0x0042,
    0x00d7, 0x003d, 0x009c, 0x00b4,
};

unsigned char DoublesdataSource[48 * 8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

double *DoublesData = (double *)DoublesdataSource;
short MysteryBiomeDataArrayRepeatedTwice[512];
short MysteryBiomeDataArrayRepeatedTwiceMod12[512];

void ConstructStatics() {

	int idx;
	short value;

	sqrt312 = (sqrt(3.0) - 1.0) / 2.0;
	sqrt336 = (3.0 - sqrt(3.0)) / 6.0;

	idx = 0;
	do {
		value = MysteryBiomeDataArray[idx & 0xff];
		MysteryBiomeDataArrayRepeatedTwice[idx] = value;
		MysteryBiomeDataArrayRepeatedTwiceMod12[idx] = value % 12;
		idx = idx + 1;
	} while (idx < 0x200);
	return;
}

void LogStatics() {
	for (int i = 0; i < 48; i++) {
		printf("%f\n", DoublesData[i]);
	}
	for (int i = 0; i < 512; i++) {
		printf("%d\n", MysteryBiomeDataArrayRepeatedTwice[i]);
	}
}

double ComputeMagicValueFromDoubles(double x, double y, double z) {
	uint uVar1;
	uint uVar2;
	double dVar3;
	double dVar4;
	double dVar5;
	double dVar6;
	double dVar7;
	double dVar8;
	double dVar9;
	double dVar10;
	double dVar11;

	dVar7 = (x + y) * sqrt312;
	dVar6 = dVar7 + x;
	uVar2 = (uint)dVar6;
	if (dVar6 < (double)uVar2) {
		uVar2 = uVar2 - 1;
	}
	dVar7 = dVar7 + y;
	uVar1 = (uint)dVar7;
	if (dVar7 < (double)uVar1) {
		uVar1 = uVar1 - 1;
	}
	dVar6 = (double)(uVar1 + uVar2) * sqrt336;
	dVar10 = x - ((double)uVar2 - dVar6);
	dVar9 = y - ((double)uVar1 - dVar6);
	uVar1 = uVar1 & 0xff;
	uVar2 = uVar2 & 0xff;
	dVar8 = 0.0;
	dVar7 = (dVar10 - (double)(uint)(dVar9 < dVar10)) + sqrt336;
	dVar3 = (dVar9 - (double)(uint)(dVar10 <= dVar9)) + sqrt336;
	dVar11 = (dVar10 - 1.0) + sqrt336 * 2.0;
	dVar4 = (dVar9 - 1.0) + sqrt336 * 2.0;
	dVar5 = (0.5 - dVar10 * dVar10) - dVar9 * dVar9;
	dVar6 = dVar8;
	if (0.0 <= dVar5) {
		dVar6 =
		    (DoublesData[MysteryBiomeDataArrayRepeatedTwiceMod12
						 [(int)MysteryBiomeDataArrayRepeatedTwice
							[uVar1] +
						  uVar2] *
					   4 +
				     1] *
			   dVar9 +
		     DoublesData
				 [MysteryBiomeDataArrayRepeatedTwiceMod12
					[(int)MysteryBiomeDataArrayRepeatedTwice[uVar1] +
					 uVar2] *
				  4] *
			   dVar10) *
		    dVar5 * dVar5 * dVar5 * dVar5;
	}
	dVar5 = (0.5 - dVar7 * dVar7) - dVar3 * dVar3;
	if (0.0 <= dVar5) {
		dVar7 =
		    (DoublesData[MysteryBiomeDataArrayRepeatedTwiceMod12
						 [(int)MysteryBiomeDataArrayRepeatedTwice
							[(dVar10 <= dVar9) + uVar1] +
						  uVar2 + (uint)(dVar9 < dVar10)] *
					   4 +
				     1] *
			   dVar3 +
		     DoublesData[MysteryBiomeDataArrayRepeatedTwiceMod12
					   [(int)MysteryBiomeDataArrayRepeatedTwice
						  [(dVar10 <= dVar9) + uVar1] +
					    uVar2 + (uint)(dVar9 < dVar10)] *
				     4] *
			   dVar7) *
		    dVar5 * dVar5 * dVar5 * dVar5;
	} else {
		dVar7 = 0.0;
	}
	dVar3 = (0.5 - dVar11 * dVar11) - dVar4 * dVar4;
	if (0.0 <= dVar3) {
		dVar8 =
		    (DoublesData[MysteryBiomeDataArrayRepeatedTwiceMod12
						 [(int)MysteryBiomeDataArrayRepeatedTwice
							[uVar1 + 1] +
						  uVar2 + 1] *
					   4 +
				     1] *
			   dVar4 +
		     DoublesData[MysteryBiomeDataArrayRepeatedTwiceMod12
					   [(int)MysteryBiomeDataArrayRepeatedTwice
						  [uVar1 + 1] +
					    uVar2 + 1] *
				     4] *
			   dVar11) *
		    dVar3 * dVar3 * dVar3 * dVar3;
	}
	return (dVar7 + dVar6 + dVar8) * 70.0;
}

char proc(double x, double y) {
	uint subchunk_y;
	uint subchunk_x;
	int chunk_x;
	int chunk_y;
	double shifted_y;
	double dVar1;
	double shifted_x;
	int new_x;
	int new_y;
	double x2;
	double y2;
	char biome, new;

	shifted_x = x + BASE_X;
	shifted_y = y + BASE_Y;
	subchunk_x = (int)shifted_x & 0x1ff;
	subchunk_y = (int)shifted_y & 0x1ff;
	new_x = BIOME_W;
	chunk_x = ((int)shifted_x >> 9) % new_x;
	chunk_y = (int)shifted_y >> 9;
	if (chunk_x < 0) {
		chunk_x = chunk_x + new_x;
	}
	new_y = BIOME_H + -1;
	if (chunk_y < new_y) {
		new_y = chunk_y;
	}
	chunk_y = 0;
	if (0 < new_y) {
		chunk_y = new_y;
	}
	biome = SampleBiomeMapClampedWrapping(chunk_x, chunk_y);
	y2 = shifted_y;
	x2 = shifted_x;
	if (subchunk_x < 0x2a) {
		new_x = chunk_x + -1;
		new = SampleBiomeMapClampedWrapping(new_x, chunk_y);
		new_y = chunk_y;
		if (new == biome) {
			goto SampleMap;
		}
	} else {
	SampleMap:
		if (subchunk_y < 42) {
			new = SampleBiomeMapClampedWrapping(chunk_x, chunk_y + -1);
			new_x = chunk_x;
			new_y = chunk_y + -1;
			if (new != biome) {
				goto DoSinStuff;
			}
		}
		if (470 < subchunk_x) {
			new = SampleBiomeMapClampedWrapping(chunk_x + 1, chunk_y);
			new_x = chunk_x + 1;
			new_y = chunk_y;
			if (new != biome)
				goto DoSinStuff;
		}
		if (470 < subchunk_y) {
			new = SampleBiomeMapClampedWrapping(chunk_x, chunk_y + 1);
			new_x = chunk_x;
			new_y = chunk_y + 1;
			if (new != biome)
				goto DoSinStuff;
		}
		if (subchunk_x < 42) {
			if (subchunk_y < 42) {
				new_x = chunk_x + -1;
				new =
				    SampleBiomeMapClampedWrapping(new_x, chunk_y + -1);
				new_y = chunk_y + -1;
				if (new != biome)
					goto DoSinStuff;
			}
			if (470 < subchunk_y) {
				new_x = chunk_x + -1;
				new = SampleBiomeMapClampedWrapping(new_x, chunk_y + 1);
				new_y = chunk_y + 1;
				if (new != biome)
					goto DoSinStuff;
			}
		}
		if (subchunk_x < 471)
			goto Exit;
		if (subchunk_y < 42) {
			new_x = chunk_x + 1;
			new = SampleBiomeMapClampedWrapping(new_x, chunk_y + -1);
			new_y = chunk_y + -1;
			if (new != biome)
				goto DoSinStuff;
		}
		if (subchunk_y < 471)
			goto Exit;
		new = SampleBiomeMapClampedWrapping(chunk_x + 1, chunk_y + 1);
		if (new == biome)
			goto Exit;
		new_x = chunk_x + 1;
		new_y = chunk_y + 1;
	}
DoSinStuff:
	// printf("%d %d %d %d\n", chunk_x, chunk_y, new_x, new_y);
	new = SampleBiomeMapClampedWrapping(new_x, new_y);
	if (!SINCOS_WOBBLE) {
		x2 = ComputeMagicValueFromDoubles(x2 * 0.05, y2 * 0.05, y);
		x2 = x2 * 2.5;
		y2 = x2;
	} else {
		y2 = ComputeMagicValueFromDoubles(x2 * 0.05, y2 * 0.05, x2);
		dVar1 = sin(shifted_y * 0.005);
		x2 = cos(shifted_x * 0.005);
		x2 = x2 * 30.0 + y2 * 11.0;
		y2 = dVar1 * 30.0 + y2 * 11.0;
	}
	biome = SampleBiomeMapClampedWrapping((int)(y2 + shifted_x) >> 9,
							  (int)(x2 + shifted_y) >> 9);
Exit:
	return biome;
}

int main() {
	ConstructStatics();
	// LogStatics();
	Image img;
	unsigned short sz = 128 + (1 << 9);
	int gs = 8;
	new_image(&img, sz * gs, sz * gs);
	int x = 29 * 512, y = -7 * 512;
	x -= (sz - 512) / 2;
	y -= (sz - 512) / 2;
	Colour colours[4] = {{.r = 255}, {.g = 255}, {.b = 255}, {}};
	// Colour border = {.r = 255, .g = 255, .b = 255};
	for (int cx = 0; cx < gs; cx++) {
		for (int cy = 0; cy < gs; cy++) {
			for (int i = 0; i < sz; i++) {
				for (int j = 0; j < sz; j++) {
					int px = i + x + BIOME_W * 512 * (gs * cy + cx),
					    py = j + y;
					set_pixel(&img, i + sz * cx,
						    ((sz - j - 1) + sz * cy),
						    colours[proc(px, py)]);
				}
			}
		}
	}
	save_image(&img, "./out.bmp");
}
