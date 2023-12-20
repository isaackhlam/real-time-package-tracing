import { createRouter, createWebHistory } from 'vue-router';
import MainView from '../views/TrackView.vue';
import MainLayout from '../layouts/MainLayout.vue';

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      meta: { layout: MainLayout },
      component: MainView,
    },
  ],
});

export default router;
