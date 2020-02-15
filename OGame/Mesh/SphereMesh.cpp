#include "SphereMesh.h"

SphereMesh::SphereMesh(float _rad, class VulkanRenderer* _renderer)
{
	renderer = _renderer;
	createSphere(_rad, 32);
}

SphereMesh::~SphereMesh()
{
}


void SphereMesh::createSphere(float radius, int segments) {
	float M_PI = 3.14159265358979323846;
	int i, j, base, i0;
	float x, y, z, R;
	double theta, phi;
	int vsegs, hsegs;
	int stride = 8;

	vsegs = segments;
	if (vsegs < 2) vsegs = 2;
	hsegs = vsegs * 2;
	int nverts = 1 + (vsegs - 1) * (hsegs + 1) + 1; // top + middle + bottom
	int ntris = hsegs + (vsegs - 2) * hsegs * 2 + hsegs; // top + middle + bottom
	
	vertex_amount = nverts;
	vertexArray = new Vertex[vertex_amount];

	index_amount = ntris * 3;
	indexArray = new uint16_t[index_amount];

	// The vertex array: 3D xyz, 3D normal, 2D st (8 floats per vertex)
	// First vertex: top pole (+z is "up" in object local coords)
	vertexArray[0].pos.x = 0.0f;
	vertexArray[0].pos.y = 0.0f;
	vertexArray[0].pos.z = radius;
	vertexArray[0].normal.x = 0.0f;
	vertexArray[0].normal.y = 0.0f;
	vertexArray[0].normal.z = 1.0f;
	//vertexArray[0] = 0.5f;
	//vertexArray[0] = 1.0f;
	vertexArray[0].color = { 0.8f, 0.5f, 0.0f };
	// Last vertex: bottom pole
	base = (nverts - 1) /** stride*/;
	vertexArray[base].pos.x = 0.0f;
	vertexArray[base].pos.y = 0.0f;
	vertexArray[base].pos.z = -radius;
	vertexArray[base].normal.x = 0.0f;
	vertexArray[base].normal.y = 0.0f;
	vertexArray[base].normal.z = -1.0f;
	//vertexArray[base + 6] = 0.5f;
	//vertexArray[base + 7] = 0.0f;
	vertexArray[base].color = { 0.8f, 0.5f, 0.0f };
	// All other vertices:
	// vsegs-1 latitude rings of hsegs+1 vertices each
	// (duplicates at texture seam s=0 / s=1)
	for (j = 0; j < vsegs - 1; j++) { // vsegs-1 latitude rings of vertices
		theta = (double)(j + 1) / vsegs * M_PI;
		z = glm::cos(theta);
		R = sin(theta);
		for (i = 0; i <= hsegs; i++) { // hsegs+1 vertices in each ring (duplicate for texcoords)
			phi = (double)i / hsegs * 2.0 * M_PI;
			x = R * cos(phi);
			y = R * sin(phi);
			base = (1 + j * (hsegs + 1) + i) /** stride*/;
			vertexArray[base].pos.x = radius * x;
			vertexArray[base].pos.y = radius * y;
			vertexArray[base].pos.z = radius * z;
			vertexArray[base].normal.x = x;
			vertexArray[base].normal.y = y;
			vertexArray[base].normal.z = z;
			//vertexArray[base].tex.x = (float)i / hsegs;
			//vertexArray[base].tex.x = 1.0f - (float)(j + 1) / vsegs;
			vertexArray[base].color = { 0.8f, 0.5f, 0.0f };

		}
	}

	// The index array: triplets of integers, one for each triangle
	// Top cap
	for (i = 0; i < hsegs; i++) {
		indexArray[3 * i] = 0;
		indexArray[3 * i + 1] = 1 + i;
		indexArray[3 * i + 2] = 2 + i;
	}
	// Middle part (possibly empty if vsegs=2)
	for (j = 0; j < vsegs - 2; j++) {
		for (i = 0; i < hsegs; i++) {
			base = 3 * (hsegs + 2 * (j * hsegs + i));
			i0 = 1 + j * (hsegs + 1) + i;
			indexArray[base] = i0;
			indexArray[base + 1] = i0 + hsegs + 1;
			indexArray[base + 2] = i0 + 1;
			indexArray[base + 3] = i0 + 1;
			indexArray[base + 4] = i0 + hsegs + 1;
			indexArray[base + 5] = i0 + hsegs + 2;
		}
	}
	// Bottom cap
	base = 3 * (hsegs + 2 * (vsegs - 2) * hsegs);
	for (i = 0; i < hsegs; i++) {
		indexArray[base + 3 * i] = nverts - 1;
		indexArray[base + 3 * i + 1] = nverts - 2 - i;
		indexArray[base + 3 * i + 2] = nverts - 3 - i;
	}

	createBuffers();

};
