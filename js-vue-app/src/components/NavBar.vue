<script setup>
  import { h, ref } from 'vue';
  import { RouterLink } from 'vue-router';
  import { NIcon, NMenu, NP, useMessage } from 'naive-ui';
  import {
    MapOutline as MapIcon,
    PersonOutline as LoginIcon,
    HomeOutline as HomeIcon
  } from '@vicons/ionicons5';
  import Cookies from 'js-cookie';

  const message = useMessage();

  const meRef = ref(null);
  meRef.value = Cookies.get('x-token');

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
  ]

  const loginOption = [
    {
      label: () =>
        h(
          RouterLink,
          {
            to: {
              name: 'login',
            },
          },
          "Login"
        ),
      key: 'login',
      icon: renderIcon(LoginIcon),
    },
  ]

  const logoutOption = [
    {
      label: () => h(NP, { onClick: () => handleLogoutClick() }, 'Log Out'),
      key: 'logout',
      icon: renderIcon(LoginIcon)
    },
  ];

  const handleLogoutClick = () => {
    Cookies.remove('x-token');
    Cookies.remove('userId');
    Cookies.remove('username');
    meRef.value = undefined;
    message.success("Logout Successfully");
  };
</script>

<template>
  <div class="header-container">
    <n-menu :options="menuOptions" mode="horizontal" />
    <n-menu v-if="meRef === undefined" :options="loginOption" mode="horizontal" class="login-button" />
    <n-menu v-else :options="logoutOption" mode="horizontal" class="login-button" />
  </div>
</template>

<style scoped>
  .header-container {
    display: flex;
  }

  .login-button {
    justify-content: flex-end;
  }
</style>
