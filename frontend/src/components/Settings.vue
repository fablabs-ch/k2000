<template>
  <div>

    <v-btn color="primary" @click="tare()">Tare</v-btn>

    <v-snackbar :timeout=2000
                :top=true
                :vertical=true
                v-model="snackbar">
      {{ snacktext }}
      <v-btn flat color="pink" @click.native="snackbar = false">Close</v-btn>
    </v-snackbar>
  </div>
</template>

<script>
export default {
  name: 'settings',
  data() {
    return {
      snackbar: false,
      snacktext: ''
    }
  },
  methods: {
    tare() {
      this.$http.post('/api/command/tare').then(response => {
        this.notify('Tare done')
      }, response => {
        this.notify('Error when trying to tare')
      })
    },
    notify(message) {
      this.snacktext = message
      this.snackbar = true
    }
  }
}
</script>

<style>

</style>

