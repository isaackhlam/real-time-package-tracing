import { createRouter, createWebHistory } from 'vue-router';
import MainView from '../views/MainView.vue';
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
    {
      path: '/track',
      name: 'track',
      meta: { layout: MainLayout },
      component: () => import('../views/TrackView.vue'),
    },
    {
      path: '/login',
      name: 'login',
      meta: { layout: MainLayout },
      component: () => import('../views/LoginView.vue'),
    },
    {
      path: '/:pathMatch(.*)*',
      name: 'not found',
      meta: { layout: MainLayout },
      component: () => import('../views/NotFoundView.vue'),
    },
  ],
});

export default router;
