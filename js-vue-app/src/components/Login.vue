<script setup>
  import { ref } from 'vue';
  import { NCard, NTabs, NTabPane, NForm, NFormItemRow, NInput, NButton } from 'naive-ui';

  // Ref
  const formRef = ref(null);
  const loginModelRef = ref({
    userId: null,
    password: null,
  });
  const registerModelRef = ref({
    userId: null,
    username: null,
    password: null,
    reenteredPassword: null,
  });
  const reenteredPasswordItemRef = ref(null);

  // Validator and Form Rule
  const validatePasswordSame = (_rule, value) =>
    value === registerModelRef.value.password;

  const RegisterRules = {
    userId: [
      {
        required: true,
        message: 'User ID is required'
      }
    ],
    username: [
      {
        required: false,
      }
    ],
    password: [
      {
        required: true,
        message: 'Password is required'
      }
    ],
    reenteredPassword: [
      {
        required: true,
        message: 'Re-entered password is required',
        trigger: ['input', 'blur']
      },
      {
        validator: validatePasswordSame,
        message: 'Password is not same as re-entered password',
        trigger: ['input', 'blur', 'password-input']
      }
    ]
  };

  const LoginRules = {
    userId: [
      {
        required: true,
        message: 'Username is required'
      }
    ],
    password: [
      {
        required: true,
        message: 'Password is required'
      }
    ]
  };

  // Button and Input Handler
  const handlePasswordInput = () => {
    if (registerModelRef.value.reenteredPassword) {
      reenteredPasswordItemRef.value.validate({ trigger: 'password-input' });
    }
  };

  const handleRegisterButtonClick = (e) => {
    e.preventDefault();
    formRef.value?.validate((errors) => {
      if (!errors) {
        const formData = JSON.stringify(formRef.value.model);
        console.log(formData);
      } else {
        console.log(errors);
      }
    });
  };

  const handleLoginButtonClick = () => {
    const formData = JSON.stringify(formRef.value.model);
    console.log(formData);
  };

</script>

<template>
  <n-card>
    <n-tabs
      class="card-tabs"
      default-value="signin"
      size="large"
      animated
      pane-wrapper-style="margin: 0 -4px"
      pane-style="padding-left: 4px; padding-right: 4px; box-sizing: border-box;"
    >
      <n-tab-pane name="signin" tab="Sign in">
        <n-form ref="formRef" :model="loginModelRef" :rules="LoginRules">
          <n-form-item-row label="UserId" path="userId">
            <n-input v-model:value="loginModelRef.userId" @keydown.enter.prevent />
          </n-form-item-row>
          <n-form-item-row label="Password" path="password">
            <n-input v-model:value="loginModelRef.password" type="password" @keydown.enter.prevent />
          </n-form-item-row>
        </n-form>
        <n-button
          type="primary"
          block
          secondary
          strong
          :disabled="loginModelRef.userId === null"
          @click="handleLoginButtonClick"
        >
          Sign In
        </n-button>
      </n-tab-pane>
      <n-tab-pane name="signup" tab="Sign up">
        <n-form ref="formRef" :model="registerModelRef" :rules="RegisterRules">
          <n-form-item-row label="UserId" path="userId">
            <n-input v-model:value="registerModelRef.userId" @keydown.enter.prevent />
          </n-form-item-row>
          <n-form-item-row label="UserName" path="username">
            <n-input v-model:value="registerModelRef.username" @keydown.enter.prevent />
          </n-form-item-row>
          <n-form-item-row label="Password" path="password">
            <n-input
              v-model:value="registerModelRef.password"
              type="password"
              @input="handlePasswordInput"
              @keydown.enter.prevent/>
          </n-form-item-row>
          <n-form-item-row label="Reenter Password" path="reenteredPassword" ref="reenteredPasswordItemRef">
            <n-input v-model:value="registerModelRef.reenteredPassword" type="password" @keydown.enter.prevent />
          </n-form-item-row>
        </n-form>
        <n-button
          type="primary"
          block
          secondary
          strong
          :disabled="registerModelRef.userId === null"
          @click="handleRegisterButtonClick"
        >
          Sign up
        </n-button>
      </n-tab-pane>
    </n-tabs>
  </n-card>
</template>
