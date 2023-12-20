<script setup>
  import Heading from './components/Heading.vue';
  import Map from './components/Map.vue';
</script>

<template>
  <div class="app">
    <Heading />
    <Map />
  </div>
</template>

<style>
  body {
    margin: 0;
    font-family: Inter, system-ui, Avenir, Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
  }

  code {
    font-family: source-code-pro, Menlo, Monaco, Consolas, 'Courier New', monospace;
  }

  .app {
    text-align: center;
  }
</style>
