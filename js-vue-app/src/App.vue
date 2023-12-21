<script setup>
  import { RouterView } from 'vue-router';
  import { NMessageProvider } from 'naive-ui';
</script>

<template>
  <n-message-provider>
    <component :is="$route.meta.layout || 'div'">
      <RouterView />
    </component>
  </n-message-provider>
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
</style>
