<script setup>
  import { h } from 'vue';
  import { RouterLink } from 'vue-router';
  import { NIcon, NMenu } from 'naive-ui';
  import {
    MapOutline as MapIcon,
    PersonOutline as LoginIcon,
    HomeOutline as HomeIcon
  } from '@vicons/ionicons5';

const renderIcon = (icon) => {
  return () => h(NIcon, null, { default: () => h(icon) })
}

const menuOptions = [
  {
    label: () =>
      h(
        RouterLink,
        {
          to: {
            name: 'home',
          }
        },
        "Home"
      ),
    key: 'home',
    icon: renderIcon(HomeIcon)
  },
  {
    label: () =>
      h(
        RouterLink,
        {
          to: {
            name: 'track',
          }
        },
        "Track"
      ),
    key: 'track',
    icon: renderIcon(MapIcon)
  },
  {
    label: () =>
      h(
        RouterLink,
        {
          to: {
            name: 'login',
          }
        },
        "Login"
      ),
    key: 'login',
    icon: renderIcon(LoginIcon)
  },
]

</script>

<template>
    <n-menu :options="menuOptions" mode="horizontal" />
</template>

<style scoped>
</style>
