<script setup>
  import { Map, NavigationControl } from 'maplibre-gl';
  import { shallowRef, onMounted, onUnmounted, markRaw } from 'vue';

  const mapContainer = shallowRef(null);
  const map = shallowRef(null);

  onMounted(() => {
    const apiKey = import.meta.env.VITE_MAPTILER_API_KEY;

    const initialState = { lng: 16.6266, lat: 49.2125, zoom: 14 };

    map.value = markRaw(new Map({
      container: mapContainer.value,
      style: `https://api.maptiler.com/maps/streets/style.json?key=${apiKey}`,
      center: [initialState.lng, initialState.lat],
      zoom: initialState.zoom
    }));

    map.value.addControl(new NavigationControl(), 'top-right');

  }),

  onUnmounted(() => {
    map.value?.remove();
  })
</script>

<template>
  <div class="map-wrap">
    <div class="map" ref="mapContainer"></div>
  </div>
</template>


<style scoped>
  @import '../../node_modules/maplibre-gl/dist/maplibre-gl.css';

  .map-wrap {
    position: relative;
    width: 100%;
    height: calc(100vh - 77px); /* calculate height of the screen minus the heading */
  }

  .map {
    position: absolute;
    width: 100%;
    height: 100%;
  }
</style>
