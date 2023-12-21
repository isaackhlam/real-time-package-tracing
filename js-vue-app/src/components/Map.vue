<script setup>
  import { Map, NavigationControl, Marker } from 'maplibre-gl';
  import { shallowRef, onMounted, onUnmounted, markRaw, ref } from 'vue';
  import { NInput, NButton, useMessage, NInputGroup } from 'naive-ui';
  import { request, gql } from 'graphql-request';

  const message = useMessage();

  const packageIdRef = ref(null);
  const mapContainer = shallowRef(null);
  const map = shallowRef(null);

  onMounted(() => {
    const apiKey = import.meta.env.VITE_MAPTILER_API_KEY;

    const initialState = { lng: 114.205634, lat: 22.422129, zoom: 14 };

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

  const handleSearchButtonClick = async () => {
    if (packageIdRef.value) {
      const findPacakgeQuery = gql`
        query($id: ID!) {
          findPackage(input: {id: $id}){
            location{
              longitude
              latitude
            }
            lastUpdateTime
          }
        }
      `;
      const variables = {id: packageIdRef.value};
      try {
        const data = await request("http://localhost:4000/graphql", findPacakgeQuery, variables);
        console.log(data.findPackage);
        const long = data.findPackage.location.longitude;
        const lat = data.findPackage.location.latitude;
        map.value.flyTo({ center: [long, lat], zoom: 16});
        const marker = new Marker({color: "#FF0000"})
          .setLngLat([Number(long), Number(lat)])
          .addTo(map.value);
        message.success("Last Updated Time: " + data.findPackage.lastUpdateTime);
      } catch(error) {
        console.log("Server Error: ", error);
        message.error(error.response.errors[0].message)
      }
    }
  }
</script>

<template>
    <n-input-group>
      <n-input v-model:value="packageIdRef" :style="{ width: '90%' }" placeholder="Input package Id"/>
      <n-button type="primary" @click="handleSearchButtonClick">
        Search
      </n-button>
    </n-input-group>
  <div class="map-wrap">
    <div class="map" ref="mapContainer"></div>
  </div>
</template>


<style scoped>
  @import '../../node_modules/maplibre-gl/dist/maplibre-gl.css';
  @import "https://unpkg.com/maplibre-gl/dist/maplibre-gl.css";

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
